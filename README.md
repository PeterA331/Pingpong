# Pingpong
Initialization:

System clock and GPIOs are configured using STM32CubeMX, STM32 NUCLEO-L476RG, part of STMicroelectronics’ ARM Cortex-M4 microcontroller series.

Timers are initialized to control the ball's automatic movement.

Game Start:

The ball (LED) starts in the center.

Two players each control one button (left/right).

Players press their button to "hit" the ball back.

Ball Movement:

A timer controls the ball’s automatic movement.

The ball "moves" by turning LEDs on/off in sequence to simulate motion.

After each successful hit, the ball's speed increases, making the timer interval shorter and the game progressively harder.

Player Input:

When the ball reaches a player's side, they must press their button within a short reaction window.

If they hit in time, the ball bounces back to the other side—with increased speed.

If they miss, the other player scores a point (or wins, depending on implementation).

Scoring:

A point system may be implemented (optional).

