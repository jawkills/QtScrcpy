# Toolbar Expand/Collapse Implementation Plan

> **For Droid:** REQUIRED SUB-SKILL: Use `executing-plans` skill to implement this plan task-by-task.

**Goal:** Menambahkan fitur expand/collapse pada toolbar agar lebih compact dengan toggle button.

**Architecture:** Tambah toggle button di paling atas toolbar, dengan fungsi show/hide untuk tombol-tombol yang tidak essential. State disimpan dalam member variable m_isExpanded.

**Tech Stack:** Qt 5/6, C++, Qt Designer UI files

---

## Task 1: Tambah Toggle Button di toolform.ui

**Files:**
- Modify: `QtScrcpy/ui/toolform.ui`

### Step 1: Tambah toggleExpandBtn sebagai item pertama

Setelah `<property name="topMargin">` dan sebelum `groupControlBtn`, tambahkan:

```xml
   <item>
    <widget class="QPushButton" name="toggleExpandBtn">
     <property name="toolTip">
      <string>expand/collapse toolbar</string>
     </property>
     <property name="text">
      <string/>
     </property>
    </widget>
   </item>
```

---

## Task 2: Tambah Slot dan Member Variable di toolform.h

**Files:**
- Modify: `QtScrcpy/ui/toolform.h`

### Step 1: Tambah slot declaration

Di section `private slots:`, tambahkan:
```cpp
    void on_toggleExpandBtn_clicked();
```

### Step 2: Tambah private method

Di section `private:` (setelah `updateGroupControl()`), tambahkan:
```cpp
    void updateToolbarState();
```

### Step 3: Tambah member variable

Di section `private:` (setelah `bool m_isHost = false;`), tambahkan:
```cpp
    bool m_isExpanded = false;
```

---

## Task 3: Implementasi di toolform.cpp

**Files:**
- Modify: `QtScrcpy/ui/toolform.cpp`

### Step 1: Tambah icon setup di initStyle()

Di dalam fungsi `initStyle()`, tambahkan di awal (sebelum icon lainnya):
```cpp
    IconHelper::Instance()->SetIcon(ui->toggleExpandBtn, QChar(0xf078), 15); // chevron-down
```

### Step 2: Tambah panggilan updateToolbarState() di constructor

Di akhir constructor `ToolForm::ToolForm(...)`, setelah `initStyle();`, tambahkan:
```cpp
    updateToolbarState();
```

### Step 3: Implementasi on_toggleExpandBtn_clicked()

Tambahkan fungsi baru (setelah `on_groupControlBtn_clicked`):
```cpp
void ToolForm::on_toggleExpandBtn_clicked()
{
    m_isExpanded = !m_isExpanded;
    updateToolbarState();
}
```

### Step 4: Implementasi updateToolbarState()

Tambahkan fungsi baru (setelah `updateGroupControl`):
```cpp
void ToolForm::updateToolbarState()
{
    // Update toggle button icon
    if (m_isExpanded) {
        IconHelper::Instance()->SetIcon(ui->toggleExpandBtn, QChar(0xf077), 15); // chevron-up
    } else {
        IconHelper::Instance()->SetIcon(ui->toggleExpandBtn, QChar(0xf078), 15); // chevron-down
    }

    // Tombol yang disembunyikan saat minimized
    ui->expandNotifyBtn->setVisible(m_isExpanded);
    ui->openScreenBtn->setVisible(m_isExpanded);
    ui->closeScreenBtn->setVisible(m_isExpanded);
    ui->volumeUpBtn->setVisible(m_isExpanded);
    ui->volumeDownBtn->setVisible(m_isExpanded);
    ui->appSwitchBtn->setVisible(m_isExpanded);
    ui->menuBtn->setVisible(m_isExpanded);
    ui->screenShotBtn->setVisible(m_isExpanded);

    // Resize window to fit content
    adjustSize();
}
```

---

## Task 4: Verifikasi dan Commit

### Step 1: Verifikasi perubahan

```bash
git diff --stat
```

### Step 2: Commit

```bash
git add QtScrcpy/ui/toolform.ui QtScrcpy/ui/toolform.h QtScrcpy/ui/toolform.cpp
git commit -m "feat: add expand/collapse toggle to toolbar"
```

---

## Summary

| Task | File | Aksi |
|------|------|------|
| 1 | toolform.ui | Tambah toggleExpandBtn widget |
| 2 | toolform.h | Tambah slot, method, dan member variable |
| 3 | toolform.cpp | Implementasi toggle logic dan updateToolbarState() |
| 4 | - | Verifikasi dan commit |

## Button Visibility Matrix

| Button | Minimized | Expanded |
|--------|-----------|----------|
| toggleExpandBtn | ✓ | ✓ |
| groupControlBtn | ✓ | ✓ |
| homeBtn | ✓ | ✓ |
| returnBtn | ✓ | ✓ |
| powerBtn | ✓ | ✓ |
| expandNotifyBtn | ✗ | ✓ |
| openScreenBtn | ✗ | ✓ |
| closeScreenBtn | ✗ | ✓ |
| volumeUpBtn | ✗ | ✓ |
| volumeDownBtn | ✗ | ✓ |
| appSwitchBtn | ✗ | ✓ |
| menuBtn | ✗ | ✓ |
| screenShotBtn | ✗ | ✓ |
