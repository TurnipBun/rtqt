/* ioLib.h - I/O interface library header */

/* Copyright 1984-2007 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */ 

/*
modification history
--------------------
06u,12apr07,jlk  Defect WIND00088383. S_ioLib_UNKNOWN_REQUEST change.
06t,29mar07,act  WIND00060945: ioctl() should be variable-argument function
06s,12jan07,act  add discard interface
06r,31aug06,mwv  move kernel definitions of read(),write(),close() 
                 to unistd.h (WIND00038902)
06q,21aug06,act  restore changes lost in rebase (commit policy defines and
                 ioctl commands)
06p,07jul06,kuo  added new FIOUPDATE
06o,12jun06,pcm  made changes for pthread cancellation points
06n,10may06,pcm  undid changes from  version 06m
06m,05may06,pcm  added newer FIOFSTATGET and FIOREADDIR
06l,30mar06,jlk  SPR 119715. Fixed prototype for getcwd() and _getcwd()
06k,10feb06,jlk  Changed FIOFSTATGET to FIOFSTATGET_OLD.
06j,07nov05,md   fixed errno values per POSIX
06i,24oct05,md   changed PATH_MAX count to include null terminator
06h,28sep05,pcm  changed SEM_ID countMSem in DEV_HDR to BOOL drvRefFlag
06g,07sep05,pad  Fixed prototype of user-side routines isatty(), read() and
		 write() (SPR 112005).
06f,03aug05,hya  added struct fcntl_arg
06g,11aug05,rfr  Added S_ioLib_MEDIA_CHANGED errno value
06f,15jul05,pad  Removed some function prototypes already declared in unistd.h
                 (user-side only).
06e,13jul05,hya  made removability change.
06d,20jun05,hya  Added NOSTATTBL mark to errno defines.
06c,09may05,hya  changed user APIs for POSIX compliance.
06b,28mar05,hya  added struct RENAME_STRUCT.
06a,01mar05,hya  added new ioctl commands
05z,07feb05,hya  added missing RTP prototypes
05y,10jan05,hya  Increase MAX_DIRNAMES to 148
05x,09nov04,rfr  Added FIOCOMMITFS (commit a transactional file system)
05w,01oct04,yvp  Change lseek args to use off_t (for Posix).
05v,23sep04,yvp  Added (get/set)prlimit.
05u,10sep04,jyo  SPR 100119: RT11FsLib has be obsoleted. This is reflected in
                 this file.
05t,11may04,dat  97227, chg ioGlobalStdSet from void to STATUS
05s,04mar04,dat  adding dup and dup2 APIs
05r,18feb04,dat  adding _getcwd for RTP space, adding all APIs from ioLib.c,
		 deprecating the ones not avail in RTP space.
05q,06dec03,dat  new errno numeric values
05p,07nov03,dat  ioctl is shared rtn
05o,25sep03,job  Added ifdef _WRS_KERNEL sections to allow ioLib.h to be
		 used from user and kernel mode builds.
05o,28jul03,dat  removed old 960 pragma, full proto for ioFullFileNameGet().
                 changed 64 bit ioctl numbers.
05n,22oct02,dat  documenting ioctl number ranges (SPR 7187)
05m,18jul02,jkf  SPR#24332, added S_ioLib_CANT_OVERWRITE_DIR (12)
                 Added FIOMOVE.
05l,29aug00,jgn  add const to function prototypes (SPR #30492)
05k,13dec99,jkf  added _ASMLANGUAGE, changed 64 bit ioctl to ascend
05j,03mar02,jkf  SPR#24332, added S_ioLib_CANT_OVERWRITE_DIR (12), orig by chn
05i,03dec98,lrn  add FIOTRUNC64 (SPR#23692)
05h,15oct98,lrn  added 64-bit ioctl codes for dosFsLib and rawFsLib
05g,29aug95,hdn  added S_ioLib_UNFORMATED for floppy disk driver.
05f,29dec93,jmm  added FIOTIMESET for utime() support
                 added FIOINODETONAME to translate inodes to names
		 added FIOFSTATFSGET to get information for fstatfs()
05e,02oct92,srh  added FIOGETFL ioctl code
05d,22sep92,rrr  added support for c++
05c,18sep92,smb  moved open and creat prototypes to fcntl.h.
05b,16sep92,kdl  added include of unistd.h; added L_* definitions for compat.
05a,02aug92,jcf  added creat().
04z,29jul92,smb  added include for fcntl.h. removed fopen options.
04y,22jul92,kdl	 added include of stdio.h if using delete() macro.
04x,22jul92,kdl	 removed references to delete(); added conditional macro
		 definition for delete() to use remove() instead.
04w,04jul92,jcf  cleaned up.
04v,30jun92,kdl	 added FIONCONTIG and FIOTRUNC ioctl codes; added CONTIG_MAX.
04u,26may92,rrr  the tree shuffle
04t,05dec91,rrr  moved O_ and L_ macros to their posix header files
04s,26nov91,llk  fixed delete() prototype.
04r,04oct91,rrr  passed through the ansification filter
		  -fixed #else and #endif
		  -changed READ, WRITE and UPDATE to O_RDONLY O_WRONLY and
		   O_RDWR
		  -changed VOID to void
		  -changed copyright notice
04q,10jun91.del  added pragma for gnu960 alignment.
04o,20oct90,dnw  removed "iosLib.h" and declaration that required it.
04n,19oct90,shl  added #include "iosLib.h".
04m,05oct90,dnw  deleted private routines.
		 added chdir(), getcwd(), remove(), rename()
04l,05oct90,shl  added ANSI function prototypes.
                 made #endif ANSI style.
                 added copyright notice.
04k,10aug90,dnw  added declaration of ioDefDirGet().
04j,11jul90,jcc  added FIOSCSICOMMAND.
04i,14jun90,kdl  added FIOUNMOUNT.
04h,25may90,dnw  added include of limits.h and defined MAX_FILENAME_LENGTH
		   in terms of PATH_MAX
04g,20apr90,kdl  added FIOREADDIR, FIOFSTATGET.
04f,01apr90,llk  added S_ioLib_NAME_TOO_LONG.
		 decreased MAX_DIRNAMES.
04e,17mar90,rdc  added FIOSELECT and FIOUNSELECT.
	    dab  changed O_CREAT and O_TRUNC values (from 0x80 and 0x100 to
		 001000 and 002000).  fixed spelling of S_ioLib_CANCELLED.
	    kdl  added MS-DOS functions: FIONFREE, FIOMKDIR, FIORMDIR,
		 FIOLABELGET, FIOLABELSET, FIOATTRIBSET, FIOCONTIG.
04d,27jul89,hjb  added ty protocol hook stuff: FIOPROTOHOOK,FIOPROTOARG
		   FIORBUFSET,FIOWBUFSET,FIORFLUSH,FIOWFLUSH.
04c,21apr89,dab  added FIOSYNC for sync to disk.
04b,18nov88,dnw  removed NOT_GENERIC stuff.
04a,22jun88,dnw  moved READ, WRITE, and UPDATE back to vxWorks.h.
03z,04jun88,llk  added MAX_DIRNAMES and S_ioLib_NO_DEVICE_NAME_IN_PATH for path
		   parsing.
		 added FSTAT for file types (inspired by nfs).
		 added DEFAULT_FILE_PERM and DEFAULT_DIR_PERM for newly created
		   files and directories.
03y,30apr88,gae  got read/write modes right.
03x,29mar88,gae  added FIOISATTY.  Added UNIX style open() and lseek() flags.
		 moved READ, WRITE, and UPDATE here from vxWorks.h.
03w,31dec87,jlf  added FOLLOW_LINK.
03v,01oct87,gae  added FIOGETNAME for all file descriptors.
		 added FIO[SG]ETOPTIONS for line options on devices.
03u,09sep87,dnw  added FIONBIO for sockets.
		 added FIONMSGS for pipes.
03t,09sep87,dnw  added FIOSQUEEZE and HD_1, HD_2 for rt-11 disks.
03s,09jun87,ecs  added S_ioLib_CANCELED & FIOCANCEL.
03r,14feb87,dnw  added S_ioLib_NO_FILENAME.
03q,04feb87,llk  added FIODISKCHANGE.
03p,24dec86,gae  changed stsLib.h to vwModNum.h.
03o,01dec86,dnw  increased MAX_FILENAME_LENGTH from 32 to 100.
03n,20nov86,dnw	 added S_ioLib_DISK_NOT_PRESENT.
03m,17oct86,gae	 added S_ioLib_WRITE_PROTECTED.
03l,21may86,llk	 corrected comments.
03k,23mar86,jlf  changed GENERIC to NOT_GENERIC
03j,08mar86,dnw  added S_ioLib_DEVICE_TIMEOUT.
*/

#ifndef __INCioLibh
#define __INCioLibh

#ifdef __cplusplus
extern "C" {
#endif

#include <vwModNum.h>
#include <limits.h>
#include <net/uio.h>
#include <fcntl.h>
#include <unistd.h>
#include <dllLib.h>
#include <errno.h>
#include <sys/resource.h>

#define MAX_DIRNAMES		148		/* max directory names in path*/
#define MAX_FILENAME_LENGTH	PATH_MAX	/* max chars in filename
						 * including EOS*/

/* I/O status codes */

/*
 * Always use the VxWorks macro name in WRS vxWorks source code. This just
 * allows end-customers to use posix errno values in their posix code.
 *
 * NOSTATTBL mark at end will exclude those errno definitions from being
 * included into statSymTbl, which may hide generic errno strings by
 * those IO specifics in printErrno, etc.
 */

#define S_ioLib_NO_DRIVER		ENXIO		/* NOSTATTBL */
#define S_ioLib_UNKNOWN_REQUEST		ENOTSUP		/* NOSTATTBL */
#define S_ioLib_DEVICE_ERROR		EIO		/* NOSTATTBL */	
#define S_ioLib_DEVICE_TIMEOUT		EIO		/* NOSTATTBL */
#define S_ioLib_WRITE_PROTECTED		EACCES		/* NOSTATTBL */
#define S_ioLib_DISK_NOT_PRESENT	ENXIO		/* NOSTATTBL */
#define S_ioLib_NO_FILENAME		ENOENT		/* NOSTATTBL */
#define S_ioLib_CANCELLED		ECANCELED	/* NOSTATTBL */
#define S_ioLib_NO_DEVICE_NAME_IN_PATH	ENODEV		/* NOSTATTBL */
#define S_ioLib_NAME_TOO_LONG		ENAMETOOLONG	/* NOSTATTBL */
#define S_ioLib_UNFORMATED		EIO		/* NOSTATTBL */
#define S_ioLib_CANT_OVERWRITE_DIR      EISDIR		/* NOSTATTBL */

/* 
* This errno is used by drivers to communicate the media changed condition to
* Core I/O - it should not be used outside of the I/O system
*/
#define S_ioLib_MEDIA_CHANGED		(M_ioLib | 1)


/*
 * Ioctl function number ranges:
 *
 * 0x00000000 - 0x1FFFFFFF - reserved for WindRiver use
 * 0x20000000 - 0x2FFFFFFF - unix style ioctls (networking)
 * 0x30000000 - 0x3FFFFFFF - User reserved codes
 * 0x40000000 - 0x4FFFFFFF - unix style ioctls (networking)
 * 0x50000000 - 0x7FFFFFFF - reserved for future use
 * 0x80000000 - 0x8FFFFFFF - unix style ioctls (networking)
 * 0x90000000 - 0xBFFFFFFF - reserved for future use
 * 0XC0000000 - 0xCFFFFFFF - unix style ioctls (networking)
 * 0xD0000000 - 0xFFFFFFFE - reserved for future use
 * 0xFFFFFFFF                reserved, invalid code number
 *
 * For VxWorks sub systems, the recommended way to generate
 * ioctl numbers is to use the module number (shifted right) as a base.
 * This will be okay as long as module numbers are not more than
 * 16 bits in length. (remember, module numbers are already
 * shifted left 16 bits).
 *
 *     i.e.  #define SUBSYS_IOCTL_1  ((M_subSystem>>8) | 1)
 */

/* ioctl function codes */

#define FIONREAD	1		/* get num chars available to read */
#define FIOFLUSH	2		/* flush any chars in buffers */
#define FIOOPTIONS	3		/* set options (FIOSETOPTIONS) */
#define FIOBAUDRATE	4		/* set serial baud rate */
#define FIODISKFORMAT	5		/* format disk */
#define FIODISKINIT	6		/* initialize disk directory */
#define FIOSEEK		7		/* set current file char position */
#define FIOWHERE	8		/* get current file char position */
#define FIODIRENTRY	9		/* return a directory entry (obsolete)*/
#define FIORENAME	10		/* rename a directory entry */
#define FIOREADYCHANGE	11		/* return TRUE if there has been a
					   media change on the device */
#define FIONWRITE	12		/* get num chars still to be written */
#define FIODISKCHANGE	13		/* set a media change on the device */
#define FIOCANCEL	14		/* cancel read or write on the device */
#define FIOSQUEEZE	15		/* OBSOLETED since RT11 is obsoleted */
#define FIONBIO		16		/* set non-blocking I/O; SOCKETS ONLY!*/
#define FIONMSGS	17		/* return num msgs in pipe */
#define FIOGETNAME	18		/* return file name in arg */
#define FIOGETOPTIONS	19		/* get options */
#define FIOSETOPTIONS	FIOOPTIONS	/* set options */
#define FIOISATTY	20		/* is a tty */
#define FIOSYNC		21		/* sync to disk */
#define FIOPROTOHOOK	22		/* specify protocol hook routine */
#define FIOPROTOARG	23		/* specify protocol argument */
#define FIORBUFSET	24		/* alter the size of read buffer  */
#define FIOWBUFSET	25		/* alter the size of write buffer */
#define FIORFLUSH	26		/* flush any chars in read buffers */
#define FIOWFLUSH	27		/* flush any chars in write buffers */
#define FIOSELECT	28		/* wake up process in select on I/O */
#define FIOUNSELECT	29		/* wake up process in select on I/O */
#define FIONFREE        30              /* get free byte count on device */
#define FIOMKDIR        31              /* create a directory */
#define FIORMDIR        32              /* remove a directory */
#define FIOLABELGET     33              /* get volume label */
#define FIOLABELSET     34              /* set volume label */
#define FIOATTRIBSET    35              /* set file attribute */
#define FIOCONTIG       36              /* allocate contiguous space */
#define FIOREADDIR      37              /* read a directory entry (POSIX) */
#define FIOFSTATGET_OLD 38              /* get file status info - legacy */
#define FIOUNMOUNT      39              /* unmount disk volume */
#define FIOSCSICOMMAND  40              /* issue a SCSI command */
#define FIONCONTIG      41              /* get size of max contig area on dev */
#define FIOTRUNC        42              /* truncate file to specified length */
#define FIOGETFL        43		/* get file mode, like fcntl(F_GETFL) */
#define FIOTIMESET      44		/* change times on a file for utime() */
#define FIOINODETONAME  45		/* given inode number, return filename*/
#define FIOFSTATFSGET   46              /* get file system status info */
#define FIOMOVE         47              /* move file, ala mv, (mv not rename) */

/* 64-bit ioctl codes, "long long *" expected as 3rd argument */

#define FIOCHKDSK	48
#define FIOCONTIG64	49
#define FIONCONTIG64	50
#define FIONFREE64	51
#define FIONREAD64	52
#define FIOSEEK64	53
#define FIOWHERE64	54
#define FIOTRUNC64	55

#define FIOCOMMITFS	56
#define FIODATASYNC	57		/* sync to I/O data integrity */
#define FIOLINK		58		/* create a link */
#define FIOUNLINK	59		/* remove a link */
#define FIOACCESS	60		/* support POSIX access() */
#define FIOPATHCONF	61		/* support POSIX pathconf() */
#define FIOFCNTL	62		/* support POSIX fcntl() */
#define FIOCHMOD	63		/* support POSIX chmod() */
#define FIOFSTATGET     64              /* get stat info - POSIX  */
#define FIOUPDATE       65              /* update dosfs default create option */


/* These are for HRFS but can be used for other future file systems */
#define FIOCOMMITPOLICYGETFS 66		/* get the file system commit policy */
#define FIOCOMMITPOLICYSETFS 67		/* set the file system commit policy */
#define FIOCOMMITPERIODGETFS 68		/* get the file system's periodic  */
                                        /* commit interval in milliseconds */
#define FIOCOMMITPERIODSETFS 69		/* set the file system's periodic  */
                                        /* commit interval in milliseconds */

/* File system commit policies */
#define FS_COMMIT_POLICY_NONE     0	/* Do not commit or commits not     */
					/* supported  */
#define FS_COMMIT_POLICY_AUTO     1	/* Commit after any disk modifying  */
                                        /* operation (write, trunc() etc.)  */
#define FS_COMMIT_POLICY_MANUAL   2	/* Application does the commit      */
				        /* manually through the FIOCOMMITFS */
					/* ioctl command                    */
#define FS_COMMIT_POLICY_PERIODIC 3     /* commit is done automatically by  */
					/* the file system at specified     */
					/* fixed intervals                  */

/* the next two ioctls are for block-type storage media (e.g., disks) */
#define	FIODISCARDGET	70	/* does hardware want DISCARDs? */
#define	FIODISCARD	71	/* mark sectors (sectorRange) as deleted */
/* structure passed through "mark unused, can discard these sectors" ioctl */
typedef struct {
    long long startSector;
    unsigned int nSectors; /* or unsigned long long? */
    } SECTOR_RANGE;

/* TODO: need to consolidate ioctl codes from a few files to avoid collision */


/* ioctl option values */

#define OPT_ECHO	0x01		/* echo input */
#define OPT_CRMOD	0x02		/* lf -> crlf */
#define OPT_TANDEM	0x04		/* ^S/^Q flow control protocol */
#define OPT_7_BIT	0x08		/* strip parity bit from 8 bit input */
#define OPT_MON_TRAP	0x10		/* enable trap to monitor */
#define OPT_ABORT	0x20		/* enable shell restart */
#define OPT_LINE	0x40		/* enable basic line protocol */

#define OPT_RAW		0		/* raw mode */

#define OPT_TERMINAL	(OPT_ECHO | OPT_CRMOD | OPT_TANDEM | \
			 OPT_MON_TRAP | OPT_7_BIT | OPT_ABORT | OPT_LINE)

#define CONTIG_MAX	-1		/* "count" for FIOCONTIG if requesting
					 *  maximum contiguous space on dev
					 */

/* miscellaneous */

#define FOLLOW_LINK	-2			/* value for driver to return */

#define DEFAULT_FILE_PERM	0000640		/* default file permissions
						   unix style rw-r----- */
#define DEFAULT_DIR_PERM	0000750		/* default directory permissions
						   unix style rwxr-x--- */

/* file types -- NOTE:  these values are specified in the NFS protocol spec */

#define FSTAT_DIR		0040000		/* directory */
#define FSTAT_CHR		0020000		/* character special file */
#define FSTAT_BLK		0060000		/* block special file */
#define FSTAT_REG		0100000		/* regular file */
#define FSTAT_LNK		0120000		/* symbolic link file */
#define FSTAT_NON		0140000		/* named socket */

/* Device Header <drvRefFlag> values */

#define DEV_HDR_REMOVABLE       0x0001

/* ioctl augmented arguments */

#ifndef _ASMLANGUAGE
/* the following is obsolete and only used now by rt-11 */

typedef struct		/* REQ_DIR_ENTRY */
    {
    int entryNum;		/* number of directory entry */
    char name[MAX_FILENAME_LENGTH];	/* name of file */
    int nChars;			/* number of chars in file */
    short day;			/* creation day of month */
    short month;		/* creation month of year */
    short year;			/* creation year of era */
    } REQ_DIR_ENTRY;

/* INODE_TO_NAME_IOCTL is used to call FIOINODETONAME */
						 
typedef struct
    {
    ULONG  inode;		/* file inode */
    char * fileName;		/* pointer to string to hold file name */
    } INODE_TO_NAME_IOCTL;

/*
 * Used to provide for fcntl support via ioctl
 */
typedef struct fcntl_arg
    {
    int command;			/* 2nd arg of fcntl */
    void *data;				/* the data in/out */
    } FCNTL_ARG;

/* disk formats */

#define SS_1D_8		1	/* single side, single density, 8"     */
#define SS_2D_8		2	/* single side, double density, 8"     */
#define DS_1D_8		3	/* double side, single density, 8"     */
#define DS_2D_8		4	/* double side, double density, 8"     */
#define SS_1D_5		5	/* single side, single density, 5 1/4" */
#define SS_2D_5		6	/* single side, double density, 5 1/4" */
#define DS_1D_5		7	/* double side, single density, 5 1/4" */
#define DS_2D_5		8	/* double side, double density, 5 1/4" */

#define HD_1		129	/* hard disk - type 1 */
#define HD_2		130	/* hard disk - type 2 */

/* iosDevDelete & iosDrvRemove return codes */
#define DELETE_DONE	OK
#define REFCNT_NOT_ZERO	1
#define DELETE_ERROR	ERROR

/* globals */

/* APIs common to Kernel and RTP Space */

extern STATUS	unlink (const char *);
extern int	dup (int);
extern int	dup2 (int, int);
extern int 	ioctl (int fd, int function, ...);
extern int	rename (const char *, const char *);
extern off_t	lseek (int, off_t, int);
extern int      readv (int fd, struct iovec *iov, int iovcnt);
extern int      writev (int fd, struct iovec * iov, int iovcnt);
extern STATUS 	ioDefPathSet (const char * name);
extern void 	ioDefPathGet (char * pathname);
extern STATUS	chdir (const char *);
extern char *	getcwd (char *, size_t);
extern char *	getwd (char * pathname);

#ifdef _WRS_KERNEL

/* APIs unique to Kernel */
extern int	open (const char *, int, int);
extern int	creat (const char *, int);
extern STATUS	remove (const char *);
extern BOOL	isatty (int fd);

extern int ioMaxLinkLevels;	/* max number of symbolic links to traverse */

/* external structures (prevents include loops) */

typedef struct dev_hdr	/* DEV_HDR - device header for all device structures */
    {
    DL_NODE	node;		/* device linked list node */
    short	drvNum;		/* driver number for this device */
    const char *name;		/* device name */
    int		drvRefCount;	/* counter of concurrent driver invocations */
    UINT32      drvRefFlag;	/* driver reference flags */
    void       *pDrvEntry;	/* driver table of this device */
    FUNCPTR     deleteDrv;	/* driver called upon device delete */
    } DEV_HDR;

/*
 * Used to provide for both new and old file names in rename and move.
 * Device driver ioctl can cast the 3rd arg as a pointer to
 * RENAME_STRUCT. If not interested, it remains compatible
 * with a pointer to new, destination file name string.
 */
typedef struct
    {
    char newname [MAX_FILENAME_LENGTH];	/* New, destination file name */
    char *oldname;			/* Old, original file name */
    } RENAME_STRUCT;

extern STATUS 	ioFullFileNameGet (const char * pathName,
				   struct dev_hdr ** ppDevHdr,
				   char * fullFileName);
extern STATUS 	ioDefPathCat (const char * name);
extern void 	ioDefDevGet (char * devName); /* RTP ??? */
extern void 	ioDefDirGet (char * dirName); /* RTP ??? */
extern int 	ioGlobalStdGet (int stdFd);
extern STATUS 	ioGlobalStdSet (int stdFd, int newFd);
extern int 	ioTaskStdGet (int taskId, int stdFd);
extern STATUS 	ioTaskStdSet (int taskId, int stdFd, int newFd);

#else

/* APIs unique to RTP space */

extern int	open (const char *, int, ...);
extern int	creat (const char *, mode_t);
extern ssize_t	read (int, void *, size_t);
extern ssize_t	write (int, const void *, size_t);

extern int	close (int);
extern int	remove (const char *);

extern int	isatty (int fd);
extern char *	_getcwd (char *, size_t);
extern int	_open (const char *, int, int);
extern int      _creat (const char *, mode_t);
extern int      _read (int, void*, size_t);
extern int      _write (int, const void *, size_t);
extern int 	_ioctl (int fd, int function, int arg);
extern int      _close (int);
extern int	dup (int);
extern int	dup2 (int,int);
extern int	pipe (int fildes[2]);
extern int	getprlimit (int idtype, int id, int resource, 
			    struct rlimit * rlp);
extern int	setprlimit (int idtype, int id, int resource, 
			    struct rlimit * rlp);
extern size_t	rtpIoTableSizeGet (RTP_ID rtpId);
extern STATUS	rtpIoTableSizeSet (RTP_ID rtpId, size_t newSize);
/* also select, pipeDevCreate, pipeDevDelete */

/* Deprecated declarations of kernel only APIs */

extern int	ioMaxLinkLevels _WRS_DEPRECATED("not avail in RTP");

extern STATUS 	ioFullFileNameGet () _WRS_DEPRECATED("not avail in RTP");
extern STATUS 	ioDefPathCat () _WRS_DEPRECATED("not avail in RTP");
extern void 	ioDefDevGet () _WRS_DEPRECATED("not avail in RTP");
extern void 	ioDefDirGet () _WRS_DEPRECATED("not avail in RTP");
extern int 	ioGlobalStdGet () _WRS_DEPRECATED("not avail in RTP");
extern STATUS 	ioGlobalStdSet () _WRS_DEPRECATED("not avail in RTP");
extern int 	ioTaskStdGet () _WRS_DEPRECATED("not avail in RTP");
extern STATUS 	ioTaskStdSet () _WRS_DEPRECATED("not avail in RTP");

#endif

#endif /* #ifndef _ASMLANGUAGE */

/* Conditional definition of delete() for compatibility with earlier VxWorks */

#define __DELETE_FUNC  FALSE 		/* change to TRUE to use delete() */

#if  __DELETE_FUNC
#include "stdio.h"
#define delete(filename)  remove(filename)
#endif  /* __DELETE_FUNC */


/* Miscellaneous obsolete definitions, for backward compatibility */

#define	L_SET	SEEK_SET		/* see unistd.h */
#define L_INCR	SEEK_CUR
#define L_XTND	SEEK_END


#ifdef __cplusplus
}
#endif

#endif /* __INCioLibh */




