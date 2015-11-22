#include "file_system.h"

void init_fsys(vfs_t *fs)
{
    vnode_t node;
    node.n_drive = drive_a;
    node.n_inode.n_type = directory;
    node.n_inode.n_name = "tmp";
    fs->a_drive.append(node);
}

void add_node(vnode_t *node)
{

}

void delete_node(vnode_t *node)
{

}

void print_node(vnode_t *node)
{

}
