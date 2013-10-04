#ifndef round_node_h
#define round_node_h

struct round_node {
  struct round_grid * grid;
  struct round_node * next_round;
};

#endif /* round_node_h */
