# Remove Toolbar Buttons Implementation Plan

> **For Droid:** REQUIRED SUB-SKILL: Use `executing-plans` skill to implement this plan task-by-task.

**Goal:** Hapus 3 tombol (touchBtn, clipboardBtn, fullScreenBtn) dari toolbar video form.

**Architecture:** Menghapus widget dari UI file, menghapus slot declarations dari header, dan menghapus implementasi serta icon setup dari cpp file.

**Tech Stack:** Qt 5/6, C++, Qt Designer UI files

---

## Task 1: Hapus Tombol dari toolform.ui

**Files:**
- Modify: `QtScrcpy/ui/toolform.ui`

### Step 1: Hapus widget fullScreenBtn

Hapus seluruh block XML ini:
```xml
   <item>
    <widget class="QPushButton" name="fullScreenBtn">
     <property name="toolTip">
      <string>full screen</string>
     </property>
     <property name="text">
      <string/>
     </property>
    </widget>
   </item>
```

### Step 2: Hapus widget touchBtn

Hapus seluruh block XML ini:
```xml
   <item>
    <widget class="QPushButton" name="touchBtn">
     <property name="toolTip">
      <string>touch switch</string>
     </property>
     <property name="text">
      <string/>
     </property>
    </widget>
   </item>
```

### Step 3: Hapus widget clipboardBtn

Hapus seluruh block XML ini (di akhir layout):
```xml
   <item>
    <widget class="QPushButton" name="clipboardBtn">
     <property name="toolTip">
      <string>copy clipboard text</string>
     </property>
     <property name="text">
      <string/>
     </property>
    </widget>
    </item>
```

---

## Task 2: Hapus Slot Declarations dari toolform.h

**Files:**
- Modify: `QtScrcpy/ui/toolform.h`

### Step 1: Hapus 3 slot declarations

Hapus baris-baris ini dari section `private slots:`:
```cpp
    void on_fullScreenBtn_clicked();
    void on_touchBtn_clicked();
    void on_clipboardBtn_clicked();
```

### Step 2: Hapus member variable m_showTouch

Hapus baris ini dari section `private:`:
```cpp
    bool m_showTouch = false;
```

---

## Task 3: Hapus Implementasi dari toolform.cpp

**Files:**
- Modify: `QtScrcpy/ui/toolform.cpp`

### Step 1: Hapus icon setup untuk 3 tombol

Dalam fungsi `initStyle()`, hapus 3 baris ini:
```cpp
    IconHelper::Instance()->SetIcon(ui->fullScreenBtn, QChar(0xf0b2), 15);
    IconHelper::Instance()->SetIcon(ui->touchBtn, QChar(0xf111), 15);
    IconHelper::Instance()->SetIcon(ui->clipboardBtn, QChar(0xf0c5), 15);
```

### Step 2: Hapus fungsi on_fullScreenBtn_clicked()

Hapus seluruh fungsi ini (sekitar baris 105-113):
```cpp
void ToolForm::on_fullScreenBtn_clicked()
{
    auto device = qsc::IDeviceManage::getInstance().getDevice(m_serial);
    if (!device) {
        return;
    }

    dynamic_cast<VideoForm*>(parent())->switchFullScreen();
}
```

### Step 3: Hapus fungsi on_touchBtn_clicked()

Hapus seluruh fungsi ini (sekitar baris 195-204):
```cpp
void ToolForm::on_touchBtn_clicked()
{
    auto device = qsc::IDeviceManage::getInstance().getDevice(m_serial);
    if (!device) {
        return;
    }

    m_showTouch = !m_showTouch;
    device->showTouch(m_showTouch);
}
```

### Step 4: Hapus fungsi on_clipboardBtn_clicked()

Hapus seluruh fungsi ini (di akhir file):
```cpp
void ToolForm::on_clipboardBtn_clicked()
{
    auto device = qsc::IDeviceManage::getInstance().getDevice(m_serial);
    if (!device) {
        return;
    }
    device->requestDeviceClipboard();
}
```

---

## Task 4: Verifikasi dan Commit

### Step 1: Verifikasi perubahan

```bash
git diff --stat
```

Expected: 3 files changed (toolform.ui, toolform.h, toolform.cpp)

### Step 2: Commit

```bash
git add QtScrcpy/ui/toolform.ui QtScrcpy/ui/toolform.h QtScrcpy/ui/toolform.cpp
git commit -m "feat: remove touchBtn, clipboardBtn, fullScreenBtn from toolbar"
```

---

## Summary

| Task | File | Aksi |
|------|------|------|
| 1 | toolform.ui | Hapus 3 widget QPushButton |
| 2 | toolform.h | Hapus 3 slot declarations + 1 member variable |
| 3 | toolform.cpp | Hapus 3 icon setup + 3 fungsi implementasi |
| 4 | - | Verifikasi dan commit |
