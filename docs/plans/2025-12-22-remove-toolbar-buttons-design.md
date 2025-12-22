# Desain: Hapus 3 Tombol dari Toolbar

**Tanggal:** 2025-12-22  
**Status:** Approved

## Ringkasan

Menghapus 3 tombol yang tidak diperlukan dari toolbar video form (toolform).

## Tombol yang Dihapus

| Tombol | Object Name | Fungsi |
|--------|-------------|--------|
| Touch switch | `touchBtn` | Toggle touch mode |
| Copy clipboard | `clipboardBtn` | Copy clipboard text |
| Full screen | `fullScreenBtn` | Toggle fullscreen |

## File yang Dimodifikasi

1. **toolform.ui** - Hapus 3 widget QPushButton
2. **toolform.h** - Hapus deklarasi slot terkait (jika ada)
3. **toolform.cpp** - Hapus implementasi slot dan signal connections

## Hasil

Toolbar akan memiliki **12 tombol** (dari 15 sebelumnya):
- groupControlBtn
- expandNotifyBtn
- openScreenBtn
- closeScreenBtn
- powerBtn
- volumeUpBtn
- volumeDownBtn
- appSwitchBtn
- menuBtn
- homeBtn
- returnBtn
- screenShotBtn
