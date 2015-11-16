#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

#include <QString>
#include <QVector>

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

typedef struct inode
{
    ntype   n_type;
    QString n_name;
    QString n_data;
} inode_t;

typedef struct node_ops
{
    void (*add_inode)(inode_t *);
    void (*delete_inode)(inode_t *);
    void (*print_inode)(inode_t);
} nops;

typedef struct vnode
{
    drive_t n_drive;
    inode_t n_inode;
    nops    n_ops;
} vnode_t;

void add_inode(inode_t *);
void delete_inode(inode_t *);
void print_inode(inode_t *);

#endif // FILE_SYSTEM_H

