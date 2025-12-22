# Desain: Tombol "Hubungkan Semua" & "Tutup Semua"

**Tanggal:** 2025-12-22  
**Status:** Approved

## Ringkasan

Menambahkan dua tombol baru di area Simple Mode untuk kemudahan kontrol multiple device.

## Lokasi UI

Dua tombol baru ditempatkan di area **Simple Mode** (`simpleGroupBox`), di bawah tombol WIFI/USB Connect yang sudah ada.

## Layout

```
┌─ Simple Mode ─────────────────────────┐
│  [WIFI Connect]    [USB Connect]      │
│  [Hubungkan Semua] [Tutup Semua]  ← NEW
│  Double click to connect: ☐ auto update
│  ┌─────────────────────────────────┐  │
│  │ (device list)                   │  │
│  └─────────────────────────────────┘  │
└───────────────────────────────────────┘
```

## Spesifikasi Tombol

| Tombol | Object Name | Aksi |
|--------|-------------|------|
| **Hubungkan Semua** | `connectAllBtn` | Iterasi semua device di `connectedPhoneList`, panggil `startServer` untuk masing-masing |
| **Tutup Semua** | `disconnectAllBtn` | Panggil `disconnectAllDevice()` (fungsi existing) |

## File yang Dimodifikasi

1. **dialog.ui** - Tambah 2 QPushButton dalam layout horizontal baru
2. **dialog.h** - Deklarasi slot: `on_connectAllBtn_clicked()`, `on_disconnectAllBtn_clicked()`
3. **dialog.cpp** - Implementasi kedua slot

## Logika "Hubungkan Semua"

```
for each item in connectedPhoneList:
    extract serial from item text (format: "nickname-serial")
    set serialBox to this serial
    call on_startServerBtn_clicked()
    delay between connections (avoid race condition)
```

## Logika "Tutup Semua"

```
call qsc::IDeviceManage::getInstance().disconnectAllDevice()
```
(Sama dengan fungsi `on_stopAllServerBtn_clicked()` yang sudah ada)
