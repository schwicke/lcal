/*
 * $Id: nodes.hpp,v 1.5 2004/01/20 19:54:33 ulrich Exp $
 * Copyright (C) Ulrich Schwickerath
 *
 *  This file is part of lcal, a command line calculator
 *  Author: Ulrich Schwickerath, (C) 12/2000
 *
 *  This code comes with absolutly no warranty!
 *  it should not be used for production purposes whatsoever
 *
 */

#ifndef INCLUDE_NODES_HPP_
#define INCLUDE_NODES_HPP_
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>

template <class T>
class Node {
 public:
  char action;
  Node() {
    m_elem = 0;
    m_next = 0;
    action = ' ';
  }
  Node(T* elem) {
    m_elem = elem;
    m_next = 0;
    action = ' ';
  }
  Node(T* elem, const char act) {
    m_elem = elem;
    action = act;
    m_next = 0;
  }
  ~Node() {
    delete(m_elem);
    m_elem = 0;
  }
  T* element() {return m_elem;}
  Node<T>* nextnode() {return m_next;}
  void set_nextnode(Node<T>* next) {
    m_next = next;
  }

 private:
  T* m_elem;
  Node<T>* m_next;
};

template <class T>
class ListOf {
 private:
  Node <T> * m_first_node;
  Node <T> * m_current_node;
  Node <T> * m_last_node;

 public:
  ListOf() {
    m_first_node = 0;
    m_current_node = 0;
    m_last_node = 0;
  }
  ListOf(T * new_element) {
    m_first_node = new Node<T> (new_element);
    m_current_node = m_first_node;
    m_last_node = m_first_node;
  }
  ~ListOf() {
    Node <T> * tmp;
    Node <T> * nextn;
    tmp = m_first_node;
    nextn = tmp->nextnode();
    while (nextn != 0) {
      delete(tmp);
      tmp = nextn;
      nextn = tmp->nextnode();
    }
    delete(tmp);
    m_first_node = 0;
    m_current_node = 0;
    m_last_node = 0;
  }
  Node <T> *  first_node() {
    return m_first_node;
  }
  Node <T> *  last_node() {
    return m_last_node;
  }
  Node <T> *  current_node() {
    return m_current_node;
  }
  void reset() {
    m_current_node = m_first_node;
  }
  int is_first() {
    return(m_current_node == m_first_node);
  }
  int is_last() {
    return(m_current_node == m_last_node);
  }
  void move_next() {
    if (m_current_node == 0) m_current_node = m_first_node;
    if (m_current_node->nextnode() != 0) {
      m_current_node = m_current_node->nextnode();
    } else {
      m_current_node = 0;
    }
  }

  void add_elem(T * new_element, const char action) {
    Node <T> * newnode = new Node<T> (new_element, action);
    if (m_last_node == 0) {
      m_last_node = newnode;
    } else {
      m_last_node->set_nextnode(newnode);
      m_last_node = m_last_node->nextnode();
    }
  }
};

#endif  // INCLUDE_NODES_HPP_
