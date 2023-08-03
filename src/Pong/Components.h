#include "ECS/Components.h"

struct SizeComponent {
  int w;
  int h;
};

struct Player1Component {
  int moveSpeed;
};

struct Player2Component {
	int moveSpeed;
};

struct ColliderComponent {
  bool triggered;
  int transferSpeed;
};
