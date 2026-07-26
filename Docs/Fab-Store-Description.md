# SquadFormation — Fab Store Listing

## Headline

**SquadFormation — AI Group Movement & Formation Steering for Unreal Engine 5.**
Move whole squads and companion groups in coherent, navmesh-aware formations — the group-movement layer the Navigation System never shipped.

---

## Pitch (1 paragraph)

Unreal's Navigation System moves agents one at a time: crowd avoidance (RVO/Detour) keeps them from colliding, but it has no concept of a *squad* holding a shape while it travels. So RTS, tactics, stealth-companion and horde games each rebuild leader-follow steering, formation slots and obstacle handling from scratch. **SquadFormation** provides that missing layer as a single, drop-in C++ component. Put a `USquadComponent` on a leader/manager actor, add member pawns, pick a formation shape and spacing, and call `MoveSquadTo` — each member is assigned a formation slot, the slot is projected onto the navmesh so no agent is ordered onto unwalkable ground, and the member's `AIController` is issued a move order to it. The squad automatically faces its direction of travel. The formation math is exposed as a static, unit-testable function, and every entry point is Blueprint-callable.

---

## Feature Bullets

- **📐 Five Formation Shapes** — Column (single file), Line (shoulder-to-shoulder), Wedge (V behind the leader), Circle (ring around the center) and Box (filled grid), all driven by real offset math with configurable spacing.
- **🎯 Automatic Slot Assignment** — every member gets a deterministic local-space slot; add or remove members at runtime with `AddMember` / `RemoveMember` and the layout recomputes.
- **🧭 Navmesh-Projected Group Moves** — each slot is snapped onto the navmesh via `ProjectPointToNavigation` before it is issued, so agents never receive orders off the walkable surface.
- **➡️ Direction-Aware Facing** — the squad orients its whole formation toward the destination based on the group's average position, so the shape leads with the correct edge.
- **🕹️ Leader-Driven AIController Orders** — `MoveSquadTo` walks the member list, resolves each slot and calls `AIController::MoveToLocation` with a spacing-relative acceptance radius; returns how many members were actually ordered.
- **🧪 Unit-Testable Formation Math** — `ComputeLocalOffsets(Shape, Count, Spacing)` is a pure static function you can test without an actor or world.
- **🧩 Blueprint-Friendly** — `USquadComponent` is a `BlueprintSpawnableComponent`; Shape, Spacing and Members are all editor-exposed and every method is `BlueprintCallable`.
- **📦 Clean & Submission-Ready** — one focused Runtime module, full C++ source, no third-party binaries, no absolute paths, no external Marketplace dependencies.

---

## Technical Specs

| | |
|---|---|
| **Engine version** | Unreal Engine 5.8 |
| **Type** | C++ Code Plugin (full source included) |
| **Modules** | SquadFormation (Runtime) |
| **Runtime platforms** | Win64, Mac, Linux |
| **Engine module deps** | Core, CoreUObject, Engine, NavigationSystem, AIModule |
| **Content** | Demo map + example Blueprints (BP_SquadManager, BP_SquadAgent); Blueprint-exposed API, no mandatory content |
| **Third-party libs** | None |

---

## Key Classes

- `USquadComponent` — put on a leader/manager actor to move a group in formation (`AddMember`, `RemoveMember`, `MoveSquadTo`, `GetSlotWorldLocation`).
- `EFormationShape` — Column · Line · Wedge · Circle · Box.
- `USquadComponent::ComputeLocalOffsets` — static, unit-testable formation math.

---

## Target Audience

- **RTS & tactics developers** who need groups to move and hold shape, not just avoid each other.
- **Stealth / companion / squad-shooter teams** wanting believable follower and escort movement.
- **Horde / crowd-control games** that need many agents to advance as coherent units.
- **AI/gameplay programmers** who want a reusable formation layer on top of the Navigation System instead of rebuilding one per project.

---

## Suggested Price

**€119** (self-serve tier, well under the $1,500 cap).

- Optional launch discount: **€95 (−20%)** for the first two weeks to seed reviews.

---

## Suggested Tags / Keywords

Formation · Squad · AI · Group Movement · Steering · Navigation · Navmesh · RTS · Tactics · Companion AI · Gameplay Framework · C++
