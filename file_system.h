#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

#include <QString>
#include <QList>
#include <QTreeWidgetItem>

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
    QString n_extension;
    QString n_data;
} inode_t;

typedef struct node_ops
{
    void (*add_node)(inode_t *);
    void (*delete_node)(inode_t *);
    void (*print_node)(inode_t);
} nops;

typedef struct vnode
{
    drive_t          n_drive;
    inode_t          n_inode;
    nops             n_ops;
    QTreeWidgetItem *n_item;
} vnode_t;

typedef struct vir_file_sys
{
    QList<vnode_t> a_drive;
    QList<vnode_t> b_drive;
    QList<vnode_t> c_drive;
} vfs_t;

void init_fsys(vfs_t *);
void add_node(vnode_t *);
void delete_node(vnode_t *);
void print_node(vnode_t *);

#endif // FILE_SYSTEM_H

