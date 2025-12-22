# Desain: Toolbar Expand/Collapse

**Tanggal:** 2025-12-22  
**Status:** Approved

## Ringkasan

Menambahkan fitur expand/collapse pada toolbar video form agar tidak terlalu panjang.

## Behavior

| State | Tombol Terlihat |
|-------|-----------------|
| **Minimized** | Toggle ▼, Group Control, Home, Back, Power (5 tombol) |
| **Expanded** | Toggle ▲ + Semua 12 tombol (13 tombol) |

## Toggle Button

- **Object Name**: `toggleExpandBtn`
- **Icon**: Chevron down (▼) saat minimized, Chevron up (▲) saat expanded
- **Posisi**: Paling atas toolbar
- **Fungsi**: Toggle antara minimized dan expanded state

## Tombol Selalu Terlihat (Minimized Mode)

1. `toggleExpandBtn` - Toggle expand/collapse
2. `groupControlBtn` - Group control
3. `homeBtn` - Home
4. `returnBtn` - Back/Return
5. `powerBtn` - Power

## Tombol Tersembunyi saat Minimized

1. `expandNotifyBtn` - Expand notification
2. `openScreenBtn` - Open screen
3. `closeScreenBtn` - Close screen
4. `volumeUpBtn` - Volume up
5. `volumeDownBtn` - Volume down
6. `appSwitchBtn` - App switch
7. `menuBtn` - Menu
8. `screenShotBtn` - Screenshot

## State Default

Toolbar mulai dalam mode **minimized** (compact).

## Member Variable

- `bool m_isExpanded = false` - Track current state

## File yang Dimodifikasi

1. **toolform.ui** - Tambah toggleExpandBtn
2. **toolform.h** - Tambah slot dan member variable
3. **toolform.cpp** - Implementasi toggle logic dengan show/hide buttons
