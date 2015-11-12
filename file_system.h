#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

typedef enum vfs_limits
{
    max_files = 5,
    max_directories = 4,
} limits_t;

typedef enum drive
{
    drive_a,
    drive_b,
    drive_c
} drive_t;

typedef enum node_type
{
    file,
    directory
} ntype;

typedef enum node_ops
{
    add_file,
    delete_file,
    print_file
} nops;

typedef struct inode
{
    drive_t n_drive;
    QString n_name;
    QString n_ext;
    QString n_data;
} inode_t;

typedef struct vnode
{
    ntype   n_type;
    nops    n_ops;
    inode_t n_inode;
} vnode_t;

#endif // FILE_SYSTEM_H

