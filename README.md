# School Bus of the Dead

> My first raylib attempt at making a game.

## Concept

You are a school bus driver in a zombie apocalypse. Your job is ordinary:
drive kids to and from school. The one catch — the streets are full of zombies.

You plow through (and shoot) zombies on your routes, deliver every kid safely,
and the grateful parents pay you. Use that money to upgrade your bus for the
days ahead.

The game is structured in **days/rounds**. Each day you have a number of kids to
pick up and get home. Once everyone is delivered, the day ends and you spend
your earnings on upgrades for tomorrow. Every new day raises the stakes: more
zombies, new variants, and a world that changes overnight — the bridge you took
yesterday might be broken today.

Zombies can reach the bus and damage it. Be careless and you — and your
passengers — die. Keep everyone alive with upgrades like automatic guns, a
spiked snowplow, or by handing the kids guns of their own.

## Design Pillars (decided scope)

- **Action-first.** The core fun is *driving and slaughtering zombies*. The
  kids and routes are the frame; the moment-to-moment drive is the game.
- **Upgrades are felt, not stats.** Every upgrade visibly changes how the bus
  drives or kills (snowplow, auto-guns, spiked ram, armed kids) — no invisible
  "+5%" bonuses.
- **The day loop is a thin wrapper.** Days give structure and a reason to spend
  money. Briefing → drive → summary/shop → repeat. Kept minimal on purpose.
- **Fixed, handcrafted map.** One designed town, reused each day. "The world
  changed overnight" (broken bridge, blocked road) is a *scripted* variant of
  that map, not procedural generation.

### Scope target

A polished, satisfying playable loop — built as a learning project, aimed at a
**free release on itch.io**. Not commercial.

## Roadmap

Each milestone is a playable vertical slice you can hand to a friend.

1. **Close the loop once** — one kid, fixed school, coins on delivery.
   *(top priority)*
2. **Combat feel pass** — make running over / shooting zombies *feel good*
   before adding more structure. This is the pillar; prove it's fun early.
3. **Make it a day** — N kids, a "day done" condition, a summary screen;
   the game loop returns instead of looping forever.
4. **One driving-changing upgrade** — snowplow or auto-gun: coins → visible
   effect.
5. **Difficulty ramp** — day number → zombie count / speed / variant.
6. **Scripted world-change** — the broken-bridge day. The hook, now cheap
   because the map is fixed.

## Architecture (planned)

Three boxes — *what's loaded*, *what's persisting*, *what's running*:

- **Game / Assets** — loaded once, never reset: map model, zombie mesh, sounds,
  fonts. Owns the window, audio, and the state machine.
- **Session** — one playthrough's live data, shared by every screen, reset only
  on "new game": coins, day number, upgrades owned, the bus.
- **State** — the screen running now (Menu, Driving, Shop, Game Over) plus its
  own throwaway pieces (today's live zombies). Swapped by a `StateManager`.

The game loop is a **state machine**: a screen hands control back instead of
looping forever, and one owner decides what screen runs next.

## Game update

![alt text](image.png)

## C++ Skill Review (2026-06-08)

A self-assessment checkpoint for the "learn C++ deeper" goal. Snapshot of the
codebase as of this date.

### Rating: 4 / 10

Scale used:

- **1–2**: `main()`, loops, functions. Procedural C-with-classes.
- **3–4**: Comfortable with classes, inheritance, virtual functions, STL
  containers. *Thinks* in objects. ← **here, upper end**
- **5–6**: Modern idioms reflexive — RAII, smart pointers, `const`-correctness,
  references over copies, no raw `new`/`delete`. Knows *why*, not just *what*.
- **7–8**: Move semantics, templates, value categories, rule of 0/3/5 in the
  bones. Designs for ownership and lifetime deliberately. Reads the standard.
- **9–10**: Writes libraries others depend on. Memory model, ABI, UB cold.
  NASA / JPL / HFT territory.

**Why 4, not lower:** real architectural instincts. The `Screen` state machine
(`update()` returns the next screen) is a clean polymorphic FSM. Sharing one
`Model` across all zombies via `static` members is a smart resource decision.
`EnemieManager`'s destructor deletes its enemies — leaks are understood and
handled. `findAnim` (with `|`-prefix handling) is thoughtful, well-commented.

**Why 4, not higher:** the code is "C++03 with classes," not modern C++. Biggest
tell is manual memory management everywhere, plus the habit cluster below.

### Stop / start — the path to 6/10

| Stop doing | Start doing | Where |
|---|---|---|
| `vector<Enemies*>` + `new` + manual `delete` | `vector<unique_ptr<Enemies>>` + `make_unique` | `handleEnemy.hpp:78`, `handleObjektiv.hpp:35` |
| `int checkCollision(Player player)` — copies the whole Player (model + 50 particles) per enemy, per frame | `checkCollision(const Player& player)` | `handleEnemy.hpp:93` |
| `using namespace std;` in **headers** | `std::vector`, or `using` inside `.cpp` only | every `.hpp` |
| `#define ROOM_WIDTH 100` | `constexpr int ROOM_WIDTH = 100;` | `handleEnemy.hpp:8`, `global.hpp` |
| Non-mutating getters that aren't `const` | `int getMaxEnemies() const` | `handleEnemy.hpp:88`, etc. |
| `typedef struct Particles{...}Particle;` (C style) | `struct Particle { ... };` | `handlePlayer.hpp:15` |

If only one thing: replace every owning raw pointer with `std::unique_ptr`. It
forces thinking about **ownership** — the central skill separating a 4 from a 6.

### Real bugs found (learning material)

1. **`checkIfIdle` (handleEnemy.cpp:87)** — `||` of two overlapping half-lines is
   almost always true. Want `&&` + absolute distance.
2. **`GetRandomValue(-1.0f, 1.0f)`** — raylib's `GetRandomValue` takes/returns
   **ints**; range -1..1 yields only `-1, 0, 1`. Particles barely scatter.
3. **`SetRandomSeed(GetRandomValue(...))` per spawn (handleEnemy.cpp:58)** —
   reseeding the PRNG every call; seed once at startup instead.
4. **`handleGameloop.hpp` is dead, non-compiling code** — calls `updateEnemies`
   (doesn't exist) and `Pickups.draw(pos)` (takes no args). Real entry point is
   `game.cpp → Game::start() → Screen`. Delete it.
5. **`Player::checkCollision`** — three spheres on the same point is just the
   largest sphere. Rethink as one sphere or a proper AABB.

### Toward "NASA level"

Two flavors, both worth knowing:

- **Literal NASA/JPL C++ is *more* restrictive, not less.** Read *"The Power of
  10: Rules for Developing Safety-Critical Code"* (Holzmann, JPL), the **JPL
  Institutional Coding Standard**, **JSF AV C++** (F-35), **MISRA C++**. The
  ethos: no dynamic allocation after init, no recursion, every loop bounded,
  every return checked. Remove nondeterminism; prove it can't misbehave.
- **World-class general C++** — master the modern language. Roadmap:
  1. Ownership & RAII — `unique_ptr`, `shared_ptr`, rule of 0/3/5. → gets to 6.
  2. References, `const`-correctness, value categories; then move semantics.
  3. STL deeply — algorithms (`find_if`, `remove_if`) over hand loops; `span`.
  4. Templates & generic programming; a little C++20 `concepts`.
  5. UB, the memory model, tooling: run **ASan** + **UBSan** on this game, build
     with `-Wall -Wextra -Werror`, learn `clang-tidy`. Let tools prove
     correctness — this is what separates 7+ engineers.

**Books, in order:** *A Tour of C++* (Stroustrup) → *Effective Modern C++*
(Meyers — best ROI right now) → *C++ Core Guidelines* (free, read as a checklist).

**Bottom line:** a strong 4 with 6-level instincts held back by pre-2011 habits.
Not a design gap — a modernization gap. Convert raw pointers to `unique_ptr`,
pass big objects by `const&`, turn on the sanitizers → a full point, fast.
