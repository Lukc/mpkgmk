
/*
 * (+int) > 0 > rcX > rc > alpha > beta > *
 */

#define MPGKMK_ALPHA -3
#define MPKGMK_BETA -2
#define MPKGMK_RC -1

typedef struct Version {
	/* semver should be compatible
	 * x.y.z.w should be compatible
	 * x (less-like) is definitely compatible
	 *  */
	int *number;
	int numbers_count;
	char *label;
	char *build;
	char *original_string;
} Version;

typedef struct Package {
	char *name;
	Version version;
	char release; /* Shouldn’t go higher than 20 or so anyway */
} Package;

/* Possible states: enabled, disabled
 * FIXME: Should we keep defaults? */
typedef struct UseFlag {
	char *name;
	int state;
} UseFlag;

enum MPKGMK_OPERATORS {
	/* Generic operators. */
	MPKGMK_GT, MPKGMK_LT, MPKGMK_GE, MPKGMK_LE, MPKGMK_E, MPKGMK_NE,

	/* ~> operator, as it exists in several package managers already. */
	/* Stands for Same Branch */
	MPKGMK_SB
};

/*
 * FIXME: Useflags in atoms?
 */
typedef struct Atom {
	char *name;
	char operator;
	Version version;
} Atom;

typedef struct Split {
	char **directories;
	char *name;
} Split;

