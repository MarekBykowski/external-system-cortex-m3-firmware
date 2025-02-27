/*
 * Copyright (c) 2019, Arm Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Description:
 *     Intrusive circular singly-linked list.
 */

#ifndef FWK_SLIST_H
#define FWK_SLIST_H

#include <stdbool.h>

/*!
 * \addtogroup GroupLibFramework Framework
 * @{
 */

/*!
 * \addtogroup GroupLinkedList Linked Lists
 * @{
 */

/*!
 * \brief Singly-linked list.
 *
 * \internal
 * \note This structure can be safely used in the place of \ref fwk_slist_node.
 */
struct fwk_slist {
    /*! Pointer to the list head */
    struct fwk_slist_node *head;

    /*! Pointer to the list tail */
    struct fwk_slist_node *tail;
};

/*!
 * \brief Singly-linked list node.
 */
struct fwk_slist_node {
    /*! Pointer to the next node in the list */
    struct fwk_slist_node *next;
};

/*!
 * @cond
 */

/*
 * Initialize a singly-linked list.
 *
 * For internal use only.
 * See fwk_list_init(list, new) for the public interface.
 */
void __fwk_slist_init(struct fwk_slist *list);

/*
 * Retrieve the node at the head of a singly-linked list.
 *
 * For internal use only.
 * See fwk_list_head(list) for the public interface.
 */
struct fwk_slist_node *__fwk_slist_head(const struct fwk_slist *list);

/*
 * Test whether a singly-linked list is empty or not.
 *
 * For internal use only.
 * See fwk_list_is_empty(list) for the public interface.
 */
bool __fwk_slist_is_empty(const struct fwk_slist *list);

/*
 * Add a new node to the head of a singly-linked list.
 *
 * For internal use only.
 * See fwk_list_push_head(list, new) for the public interface.
 */
void __fwk_slist_push_head(
    struct fwk_slist *list,
    struct fwk_slist_node *new);

/*
 * Add a new node to the end of a singly-linked list.
 *
 * For internal use only.
 * See fwk_list_push_tail(list, new) for the public interface.
 */
void __fwk_slist_push_tail(
    struct fwk_slist *list,
    struct fwk_slist_node *new);

/*
 * Remove and return the head node from a singly-linked list.
 *
 * For internal use only.
 * See fwk_list_pop_head(list) for the public interface.
 */
struct fwk_slist_node *__fwk_slist_pop_head(struct fwk_slist *list);

/*
 * Get the next node from a singly-linked list.
 *
 * For internal use only.
 * See fwk_list_next(list, node) for the public interface.
 */
struct fwk_slist_node *__fwk_slist_next(
    const struct fwk_slist *list,
    const struct fwk_slist_node *node);

/*
 * Remove a node from a singly-linked list.
 *
 * For internal use only.
 * See fwk_list_remove(list, node) for the public interface.
 */
void __fwk_slist_remove(
    struct fwk_slist *list,
    struct fwk_slist_node *node);

/*
 * Test if a node is in a singly-linked list.
 *
 * For internal use only.
 * See fwk_list_contains(list, node) for the public interface.
 */
bool __fwk_slist_contains(
    const struct fwk_slist *list,
    const struct fwk_slist_node *node);

/*!
 * @endcond
 */

/*!
 * @}
 */

/*!
 * @}
 */

#endif /* FWK_SLIST_H */
