/**************************************************************************
			GTA PROJECT   AT division
	Copyright, 1989, The Regents of the University of California.
		         Los Alamos National Laboratory

	@(#)parse.h	1.2	4/17/91
	DESCRIPTION: Structures for parsing the state notation language.
	ENVIRONMENT: UNIX
***************************************************************************/
/* Data for these blocks are generated by the parsing routines for each
** state set.  The tables are then used to generate the run-time C code
** for the sequencer.  This decouples the parsing implementation from
** the run-time code implementation.
*/

#include	"lstLib.h" /* VxWorks "list" routines & definitions */

struct	expression			/* Expression block */
{
	struct	expression *next;	/* link to next expression */
	struct	expression *last;	/* link to last in list */
	struct	expression *left;	/* ptr to left expression */
	struct	expression *right;	/* ptr to right expression */
	int	type;			/* expression type (E_*) */
	char	*value;			/* operator or value string */
	int	line_num;		/* line number */
	char	*src_file;		/* effective source file */
};
typedef	struct	expression Expr;

struct	var				/* Variable or function definition */
{
	NODE	V_link;			/* next variable in list */
	char	*name;			/* variable name */
	char	*value;			/* initial value or NULL */
	int	type;			/* var type */
	int	length;			/* array lth (0 if not an array) */
	int	ef_num;			/* event flag bit number */
	struct	db_chan *chan;		/* ptr to db channel struct or NULL */
};
typedef	struct	var Var;

struct	db_chan			/* DB channel */
{
	NODE	D_link;			/* next db chan in list */
	char	*db_name;		/* database name */
	int	index;			/* channel array index */
	Var	*var;			/* ptr to variable definition */
	Var	*ef_var;		/* ptr to event flag variable for sync */
	int	count;			/* count for db access */
	int	mon_flag;		/* TRUE if channel is "monitored" */
	float	delta;			/* monitor dead-band */
	float	timeout;		/* monitor timeout */
};
typedef	struct	db_chan Chan;

Expr		*expression(), *link_expr();

/* Linked list definitions to get rid of yucky in-line code */
#define	allocExpr()		(Expr *)malloc(sizeof(Expr));

#define	allocVar()		(Var *)malloc(sizeof(Var));
#define	nextVar(node)		(Var *)lstNext( (NODE *)node )
#define	firstVar(head)		(Var *)lstFirst( (LIST *)head )

#define	allocChan()		(Chan *)malloc(sizeof(Chan));
#define	nextChan(node)		(Chan *)lstNext( (NODE *)node )
#define	firstChan(head)		(Chan *)lstFirst( (LIST *)head )

/* Variable types */
#define	V_NONE		0		/* not defined */
#define	V_CHAR		1		/* char */
#define	V_SHORT		2		/* short */
#define	V_INT		3		/* int (but converted to long) */
#define	V_LONG		4		/* long */
#define	V_FLOAT		5		/* float */
#define	V_DOUBLE	6		/* double */
#define	V_STRING	7		/* strings (array of char) */
#define	V_EVFLAG	8		/* event flag */
#define	V_FUNC		9		/* function (not a variable) */
#define	V_UCHAR		11		/* unsigned char */
#define	V_USHORT	12		/* unsigned short */
#define	V_UINT		13		/* unsigned int (converted to unsigned long) */
#define	V_ULONG		14		/* unsigned long */

/* Expression types */
#define	E_EMPTY		0		/* empty expression */
#define	E_CONST		1		/* numeric constant */
#define	E_VAR		2		/* variable */
#define	E_FUNC		3		/* function */
#define	E_STRING	4		/* ptr to string consatant */
#define	E_UNOP		5		/* unary operator: OP expr (-, +, or !) */
#define	E_BINOP		6		/* binary operator: expr OP expr */
#define	E_ASGNOP	7		/* assign operatro:  (=, +=, *=, etc.) */
#define	E_PAREN		8		/* parenthesis around an expression */
#define	E_SUBSCR	9	/* subscript */
#define	E_TEXT		10		/* C code or other text to be inserted */
#define	E_STMT		11		/* simple statement */
#define	E_CMPND		12		/* begin compound statement: {...} */
#define	E_IF		13		/* if statement */
#define	E_ELSE		14		/* if statement */
#define	E_WHILE		15		/* while statement */
#define	E_SS		16		/* state set statement */
#define	E_STATE		17		/* state statement */
#define	E_WHEN		18		/* when statement */
