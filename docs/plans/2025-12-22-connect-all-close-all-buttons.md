# Tombol "Hubungkan Semua" & "Tutup Semua" - Implementation Plan

> **For Droid:** REQUIRED SUB-SKILL: Use `executing-plans` skill to implement this plan task-by-task.

**Goal:** Menambahkan dua tombol di Simple Mode area untuk menghubungkan/memutuskan semua device sekaligus.

**Architecture:** Modifikasi UI Qt dengan menambah layout horizontal baru berisi 2 QPushButton, kemudian connect ke slot yang mengiterasi device list.

**Tech Stack:** Qt 5/6, C++, Qt Designer UI files

---

## Task 1: Tambah Tombol di dialog.ui

**Files:**
- Modify: `QtScrcpy/ui/dialog.ui`

### Step 1: Edit dialog.ui - tambah layout horizontal baru

Tambahkan layout baru `horizontalLayout_14` setelah `horizontalLayout_9` (yang berisi wifiConnectBtn dan usbConnectBtn), di dalam `simpleGroupBox`.

Cari bagian ini di dialog.ui:
```xml
         <item>
          <layout class="QHBoxLayout" name="horizontalLayout_9">
           ...wifiConnectBtn dan usbConnectBtn...
          </layout>
         </item>
```

Tambahkan tepat setelahnya (sebelum `horizontalLayout_13`):
```xml
         <item>
          <layout class="QHBoxLayout" name="horizontalLayout_14">
           <item>
            <widget class="QPushButton" name="connectAllBtn">
             <property name="sizePolicy">
              <sizepolicy hsizetype="Preferred" vsizetype="Maximum">
               <horstretch>0</horstretch>
               <verstretch>0</verstretch>
              </sizepolicy>
             </property>
             <property name="text">
              <string>Connect All</string>
             </property>
            </widget>
           </item>
           <item>
            <widget class="QPushButton" name="disconnectAllBtn">
             <property name="sizePolicy">
              <sizepolicy hsizetype="Preferred" vsizetype="Maximum">
               <horstretch>0</horstretch>
               <verstretch>0</verstretch>
              </sizepolicy>
             </property>
             <property name="text">
              <string>Disconnect All</string>
             </property>
            </widget>
           </item>
          </layout>
         </item>
```

### Step 2: Verifikasi perubahan UI

Buka Qt Designer atau build project untuk memastikan tombol muncul dengan benar.

---

## Task 2: Deklarasi Slot di dialog.h

**Files:**
- Modify: `QtScrcpy/ui/dialog.h`

### Step 1: Tambah deklarasi slot

Cari bagian `private slots:` di dialog.h, tambahkan setelah `on_wifiConnectBtn_clicked()`:

```cpp
    void on_connectAllBtn_clicked();
    void on_disconnectAllBtn_clicked();
```

---

## Task 3: Implementasi Slot di dialog.cpp

**Files:**
- Modify: `QtScrcpy/ui/dialog.cpp`

### Step 1: Implementasi on_connectAllBtn_clicked()

Tambahkan fungsi ini di dialog.cpp (setelah `on_wifiConnectBtn_clicked`):

```cpp
void Dialog::on_connectAllBtn_clicked()
{
    int count = ui->connectedPhoneList->count();
    if (count == 0) {
        outLog("No devices found in list");
        return;
    }

    outLog("Connecting all devices...", false);

    for (int i = 0; i < count; ++i) {
        QString itemText = ui->connectedPhoneList->item(i)->text();
        // Format: "nickname-serial" - extract serial (last part after last dash)
        int lastDash = itemText.lastIndexOf('-');
        if (lastDash == -1) {
            continue;
        }
        QString serial = itemText.mid(lastDash + 1);

        // Find and select in serialBox
        int index = ui->serialBox->findText(serial);
        if (index != -1) {
            ui->serialBox->setCurrentIndex(index);
            on_startServerBtn_clicked();
            delayMs(500); // Small delay between connections
        }
    }
}
```

### Step 2: Implementasi on_disconnectAllBtn_clicked()

Tambahkan fungsi ini setelah `on_connectAllBtn_clicked`:

```cpp
void Dialog::on_disconnectAllBtn_clicked()
{
    outLog("Disconnecting all devices...", false);
    on_stopAllServerBtn_clicked();
}
```

---

## Task 4: Tambah Translation String (Opsional)

**Files:**
- Modify: `QtScrcpy/res/i18n/en_US.ts`
- Modify: `QtScrcpy/res/i18n/zh_CN.ts`

### Step 1: Update translation files

Jika ingin mendukung multi-bahasa, tambahkan string translation untuk "Connect All" dan "Disconnect All" di file .ts yang relevan.

---

## Task 5: Build dan Test

### Step 1: Build project

```bash
cd QtScrcpy
mkdir build && cd build
cmake ..
cmake --build .
```

### Step 2: Manual testing checklist

1. ☐ Buka aplikasi
2. ☐ Centang "Use Simple Mode"
3. ☐ Verifikasi tombol "Connect All" dan "Disconnect All" muncul
4. ☐ Hubungkan beberapa device (via USB atau WiFi)
5. ☐ Klik "Connect All" - semua device harus terhubung
6. ☐ Klik "Disconnect All" - semua koneksi harus terputus

### Step 3: Commit

```bash
git add QtScrcpy/ui/dialog.ui QtScrcpy/ui/dialog.h QtScrcpy/ui/dialog.cpp
git commit -m "feat: add Connect All and Disconnect All buttons in Simple Mode"
```

---

## Summary

| Task | File | Aksi |
|------|------|------|
| 1 | dialog.ui | Tambah 2 QPushButton dalam layout baru |
| 2 | dialog.h | Deklarasi 2 slot baru |
| 3 | dialog.cpp | Implementasi logika connect/disconnect all |
| 4 | *.ts | Translation strings (opsional) |
| 5 | - | Build dan test manual |
