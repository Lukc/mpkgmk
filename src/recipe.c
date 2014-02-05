#include <stdlib.h>
#include <string.h>

#include <yaml.h>

#include "recipe.h"
#include "ui.h"
#include "error.h"

RecipeElement*
recipe_alist_get(RecipeAList *alist, char *key) {
	while (alist) {
		if (!strcmp(key, alist->key))
			return alist->element;
		else
			alist = alist->next;
	}

	warning("not found");

	return (RecipeElement*) NULL;
}

char*
get_protocol(char *string) {
	int i, j;
	char *protocol;

	i = 0;
	while (string[i]) {
		if (string[i] == ':' || string[i] == '+') {
			protocol = (char*) malloc(sizeof(char) * (i+1));

			j = 0;
			while (j < i) {
				protocol[j] = string[j];
				j++;
			}

			protocol[j] = '\0';

			return protocol;
		}

		i++;
	}

	return strdup("file");
}

/*
 * TODO:
 * 	- Arrows.
 */
char*
get_filename(char *string) {
	int i;
	int last_slash;
	char *filename;

	i = 0;
	last_slash = -1;
	while (string[i]) {
		if (string[i] == '/')
			last_slash = i;
		else if (string[i] == ' ') {
			if (string[i+1] == '-' && string[i+2] == '>' && string[i+3] == ' ') {
				last_slash = i + 3;
				i += 2;
			}
				
		}

		i++;
	}

	filename = (char*) malloc(sizeof(char) * (i - last_slash));
	i = last_slash + 1;
	while (string[i]) {
		filename[i - last_slash - 1] = string[i];

		i++;
	}

	filename[i - last_slash - 1] = '\0';

	return filename;
}

char*
get_url(char *string) {
	int i, begin, end;
	char *filename;
	int seen_doubledot;

	begin = 0;
	end = 0;
	i = 0;
	seen_doubledot = 0;
	while (string[i]) {
		if (string[i] == ':') {
			seen_doubledot = 1;
		} else if (string[i] == '+') {
			if (!seen_doubledot) {
				begin = i + 1;
			}
		} else if (string[i] == ' ') {
			/* FIXME: We should be more annoying if other characters are
			 *        met. It would clearly be a syntax error. */
			if (string[i+1] == '-' &&
			    string[i+2] == '>' &&
				string[i+3] == ' ')
			{
				if (!end) {
					end = i;
				}
			}
		}

		i++;
	}

	if (!end)
		end = i;

	i = begin;
	filename = (char*) malloc(sizeof(char) * (end - begin));
	while (i < end) {
		filename[i - begin] = string[i];

		i++;
	}

	return filename;
}

Source*
string_to_source(char *string) {
	Source *source;
	source = (Source*) malloc(sizeof(Source));

	if (!source)
		return (Source*) NULL;

	source->protocol = get_protocol(string);
	source->filename = get_filename(string);
	source->url      = get_url(string);

	return source;
}

Source**
get_sources(RecipeElement *recipe) {
	RecipeElement *element;
	Source **sources, *source;
	RecipeList *list;
	int count;

	sources = (Source**) NULL;

	element = recipe_alist_get(recipe->data.alist, "source");
	if (element->type == RECIPE_STRING) {
		sources = (Source**) malloc(sizeof(Source*) * 2);
		sources[0] = string_to_source(element->data.string);
		sources[1] = NULL;
	} else if (element->type == RECIPE_LIST) {
		list = element->data.list;
		count = 0;

		while (list) {
			if (list->element->type == RECIPE_STRING) {
				count = count + 1;
				sources = (Source**) realloc(sources, sizeof(Source*) * count);

				source = string_to_source(list->element->data.string);

				sources[count-1] = source;
			} else {
				warning("A source entry is not a string.");
			}

			list = list->next;
		}

		sources = (Source**) realloc(sources, sizeof(Source*) * (count + 1));
		sources[count] = (Source*) NULL;
	} else {
		error("recipe: “source” is not a string or list.");
		exit(ERROR_BROKEN_RECIPE);
	}

	return sources;
}

#define YAML_VARIABLE    0
#define YAML_VALUE       1
#define YAML_SEQUENCE    2

/*
 * FIXME: bullshit. Or at least very buggy. Complete rewrite recommended.
 */
static void
process_yaml_layer(yaml_parser_t *parser, RecipeElement *data) {
	RecipeAList *alist;
	RecipeList *list;
	RecipeElement *element;
	yaml_event_t event;
	int storage;

	alist = data->data.alist;
	storage = YAML_VARIABLE;

	while (1) {
		yaml_parser_parse(parser, &event);

		switch (event.type) {
			case YAML_SCALAR_EVENT:
				if (storage == YAML_SEQUENCE) {
					if (!list) {
						list = (RecipeList*) malloc(sizeof(RecipeList));

						alist->element = element;
					} else {
						list->next = (RecipeList*) malloc(sizeof(RecipeList));
						list = list->next;
					}

					list->next = (RecipeList*) NULL;

					element = (RecipeElement*) malloc(sizeof(RecipeElement));
					element->type = RECIPE_STRING;
					element->data.string = strdup((char *) event.data.scalar.value);

					list->element = element;

					break;
				} else if (storage == YAML_VARIABLE) {
					if (!alist) {
						alist = (RecipeAList*) malloc(sizeof(RecipeAList));
						data->data.alist = alist;
						alist->next = (RecipeAList*) NULL;
					} else {
						alist->next = (RecipeAList*) malloc(sizeof(RecipeAList));
						alist = alist->next;
					}

					alist->key = strdup((char *) event.data.scalar.value);
				} else {
					element = (RecipeElement*) malloc(sizeof(RecipeElement));
					element->type = RECIPE_STRING;
					element->data.string = strdup((char *) event.data.scalar.value);

					alist->element = element;
				}

				storage = storage ^ YAML_VALUE;

				break;
			case YAML_SEQUENCE_START_EVENT:
				list = (RecipeList*) NULL;
				storage = YAML_SEQUENCE;
				break;
			case YAML_SEQUENCE_END_EVENT:
				error("sequence ending (%s)", alist->key);
				storage = YAML_VARIABLE;
				break;
			case YAML_MAPPING_START_EVENT:
				if (storage == YAML_SEQUENCE) {
					if (!list) {
						list = (RecipeList*) malloc(sizeof(RecipeList));
						list->next = (RecipeList*) NULL;

						list->element = (RecipeElement*) malloc(sizeof(RecipeElement));
						list->element->type = RECIPE_ALIST;
						list->element->data.alist = (RecipeAList*) malloc(sizeof(RecipeAList));

						alist = list->element->data.alist;
					} else {
						list->next = (RecipeList*) malloc(sizeof(RecipeList));
						list = list->next;
						list->next = (RecipeList*) NULL;
					}

					list->element = (RecipeElement*) malloc(sizeof(RecipeElement));
					list->element->type = RECIPE_ALIST;
					list->element->data.alist = (RecipeAList*) NULL;

					process_yaml_layer(parser, list->element);

					storage = YAML_VARIABLE;
				} else {
					if (!alist) {
						alist = (RecipeAList*) malloc(sizeof(RecipeAList));
						data->data.alist = alist;
						alist->next = (RecipeAList*) NULL;
					} else {
						alist->next = (RecipeAList*) malloc(sizeof(RecipeAList));
						alist = alist->next;
					}

					alist->element = (RecipeElement*) malloc(sizeof(RecipeElement));
					alist->element->type = RECIPE_ALIST;
					alist->element->data.alist = (RecipeAList*) NULL;

					process_yaml_layer(parser, alist->element);
				}
				storage ^= YAML_VALUE;
				break;
			case YAML_MAPPING_END_EVENT:
			case YAML_STREAM_END_EVENT:
				yaml_event_delete(&event);
				return;
			/* Ignored events, because I don’t care. */
			case YAML_STREAM_START_EVENT:
			case YAML_DOCUMENT_START_EVENT:
			case YAML_DOCUMENT_END_EVENT:
				break;
			default:
				error("Recipe parsing error: unknown yaml event type %i", event.type);
		}

		yaml_event_delete(&event);
	}
}

RecipeElement*
load_recipe(char *filename) {
	yaml_parser_t parser;
	RecipeElement *recipe, *element;
	RecipeAList *alist;
	FILE *source;

	recipe = (RecipeElement*) malloc(sizeof(RecipeElement));
	recipe->type = RECIPE_ALIST;
	recipe->data.alist = (RecipeAList*) NULL;

	source = fopen(filename, "rb");
	yaml_parser_initialize(&parser);
	yaml_parser_set_input_file(&parser, source);
	process_yaml_layer(&parser, recipe);
	yaml_parser_delete(&parser);
	fclose(source);

	/* The first level is more or less empty. Let’s get rid of it. */
	element = recipe;
	recipe = recipe->data.alist->element;
	free(element);

	alist = recipe->data.alist;
	while (alist) {
		/* FIXME: We need to substitute ${variables} and $variables in here. */
		if (!alist->element)
			info(" «« :| (%s)", alist->key);
		else
			info(" »» %s", alist->key);

		alist = alist->next;
	}

	return recipe;
}

