/**
 * @file lv_port_fs_templ.c
 *
 */

 /*Copy this file as "lv_port_fs.c" and set this value to "1" to enable content*/
#if 1

/*********************
 *      INCLUDES
 *********************/
#include "lv_port_fs.h"
#include "dfs_posix.h"
/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

typedef int file_t;
/**********************
 *  STATIC PROTOTYPES
 **********************/
static void fs_init(void);

static lv_fs_res_t fs_open (lv_fs_drv_t * drv, void * file_p, const char * path, lv_fs_mode_t mode);
static lv_fs_res_t fs_close (lv_fs_drv_t * drv, void * file_p);
static lv_fs_res_t fs_read (lv_fs_drv_t * drv, void * file_p, void * buf, uint32_t btr, uint32_t * br);
static lv_fs_res_t fs_seek (lv_fs_drv_t * drv, void * file_p, uint32_t pos);
static lv_fs_res_t fs_tell (lv_fs_drv_t * drv, void * file_p, uint32_t * pos_p);

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

int lv_port_fs_init(void)
{
    /*----------------------------------------------------
     * Initialize your storage device and File System
     * -------------------------------------------------*/
    fs_init();

    /*---------------------------------------------------
     * Register the file system interface  in LittlevGL
     *--------------------------------------------------*/

    /* Add a simple drive to open images */
    lv_fs_drv_t fs_drv;                         /*A driver descriptor*/
    lv_fs_drv_init(&fs_drv);                    /*Basic initialization*/

    /*Set up fields...*/
    fs_drv.file_size = sizeof(file_t);
    fs_drv.letter = 'S';
    fs_drv.open_cb = fs_open;
    fs_drv.close_cb = fs_close;
    fs_drv.read_cb = fs_read;
    fs_drv.seek_cb = fs_seek;
    fs_drv.tell_cb = fs_tell;

    lv_fs_drv_register(&fs_drv);

    return RT_EOK;
}
//INIT_APP_EXPORT(lv_port_fs_init);

/**********************
 *   STATIC FUNCTIONS
 **********************/

/* Initialize your Storage device and File system. */
static void fs_init(void)
{
    /*E.g. for FatFS initalize the SD card and FatFS itself*/
//    init in other position
    /*You code here*/
}

/**
 * Open a file
 * @param file_p pointer to a file_t variable
 * @param path path to the file beginning with the driver letter (e.g. S:/folder/file.txt)
 * @param mode read: FS_MODE_RD, write: FS_MODE_WR, both: FS_MODE_RD | FS_MODE_WR
 * @return LV_FS_RES_OK or any error from lv_fs_res_t enum
 */
static lv_fs_res_t fs_open (lv_fs_drv_t * drv, void * file_p, const char * path, lv_fs_mode_t mode)
{
    lv_fs_res_t res = LV_FS_RES_NOT_IMP;
    
    rt_size_t len = rt_strlen(path);
    RT_ASSERT(len > 2 && len < DFS_PATH_MAX+2);

    char posix_path[DFS_PATH_MAX] = "/lvgl/";
    const char *lvgl_dir_path = path;
    strncat(posix_path, lvgl_dir_path, DFS_PATH_MAX-6);

    int fd;
    if(mode == LV_FS_MODE_RD)
    {
        /*Open a file for read*/
        if ((fd = open(posix_path, O_RDONLY)) > 0) {
            *(file_t *)file_p = fd;
            res = LV_FS_RES_OK;         // open success
        } else {
            res = LV_FS_RES_NOT_EX;     // open fail
        }
    }

    return res;
}


/**
 * Close an opened file
 * @param file_p pointer to a file_t variable. (opened with lv_ufs_open)
 * @return LV_FS_RES_OK: no error, the file is read
 *         any error from lv_fs_res_t enum
 */
static lv_fs_res_t fs_close (lv_fs_drv_t * drv, void * file_p)
{
    lv_fs_res_t res = LV_FS_RES_UNKNOWN;

    int fd = *(file_t *)file_p;
    if (close(fd) == 0)
        res = LV_FS_RES_OK;         // close success

    return res;
}

/**
 * Read data from an opened file
 * @param file_p pointer to a file_t variable.
 * @param buf pointer to a memory block where to store the read data
 * @param btr number of Bytes To Read
 * @param br the real number of read bytes (Byte Read)
 * @return LV_FS_RES_OK: no error, the file is read
 *         any error from lv_fs_res_t enum
 */
static lv_fs_res_t fs_read (lv_fs_drv_t * drv, void * file_p, void * buf, uint32_t btr, uint32_t * br)
{
    lv_fs_res_t res = LV_FS_RES_UNKNOWN;

    int fd = *(file_t *)file_p;
    int read_bytes = read(fd, buf, btr);
    if (read_bytes >= 0) {
        *br = read_bytes;
        res = LV_FS_RES_OK;
    }
    
    return res;
}

/**
 * Set the read write pointer. Also expand the file size if necessary.
 * @param file_p pointer to a file_t variable. (opened with lv_ufs_open )
 * @param pos the new position of read write pointer
 * @return LV_FS_RES_OK: no error, the file is read
 *         any error from lv_fs_res_t enum
 */
static lv_fs_res_t fs_seek (lv_fs_drv_t * drv, void * file_p, uint32_t pos)
{
    lv_fs_res_t res = LV_FS_RES_UNKNOWN;

    int fd = *(file_t *)file_p;
    if (lseek(fd, pos, SEEK_SET) >= 0)
        res = LV_FS_RES_OK;

    return res;
}

/**
 * Give the position of the read write pointer
 * @param file_p pointer to a file_t variable.
 * @param pos_p pointer to to store the result
 * @return LV_FS_RES_OK: no error, the file is read
 *         any error from lv_fs_res_t enum
 */
static lv_fs_res_t fs_tell (lv_fs_drv_t * drv, void * file_p, uint32_t * pos_p)
{
    lv_fs_res_t res = LV_FS_RES_UNKNOWN;

    int fd = *(file_t *)file_p;
    off_t pos = lseek(fd, 0, SEEK_CUR);
    if (pos >= 0) {
        *pos_p = pos;
        res = LV_FS_RES_OK;
    }

    return res;
}

///**
// * Initialize a 'fs_read_dir_t' variable for directory reading
// * @param rddir_p pointer to a 'fs_read_dir_t' variable
// * @param path path to a directory
// * @return LV_FS_RES_OK or any error from lv_fs_res_t enum
// */
//static lv_fs_res_t fs_dir_open (lv_fs_drv_t * drv, void * rddir_p, const char *path)
//{
//    lv_fs_res_t res = LV_FS_RES_NOT_IMP;
//
//    /* Add your code here*/
//
//    return res;
//}
//
///**
// * Read the next filename form a directory.
// * The name of the directories will begin with '/'
// * @param rddir_p pointer to an initialized 'fs_read_dir_t' variable
// * @param fn pointer to a buffer to store the filename
// * @return LV_FS_RES_OK or any error from lv_fs_res_t enum
// */
//static lv_fs_res_t fs_dir_read (lv_fs_drv_t * drv, void * rddir_p, char *fn)
//{
//    lv_fs_res_t res = LV_FS_RES_NOT_IMP;
//
//    /* Add your code here*/
//
//    return res;
//}
//
///**
// * Close the directory reading
// * @param rddir_p pointer to an initialized 'fs_read_dir_t' variable
// * @return LV_FS_RES_OK or any error from lv_fs_res_t enum
// */
//static lv_fs_res_t fs_dir_close (lv_fs_drv_t * drv, void * rddir_p)
//{
//    lv_fs_res_t res = LV_FS_RES_NOT_IMP;
//
//    /* Add your code here*/
//
//    return res;
//}

#else /* Enable this file at the top */

/* This dummy typedef exists purely to silence -Wpedantic. */
typedef int keep_pedantic_happy;
#endif
