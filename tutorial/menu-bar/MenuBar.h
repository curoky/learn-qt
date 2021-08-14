/*
 * Copyright (c) 2018-2022 curoky(cccuroky@gmail.com).
 *
 * This file is part of learn-qt.
 * See https://github.com/curoky/learn-qt for further info.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once
#include <QApplication>
#include <QDebug>
#include <QIcon>
#include <QMenu>
#include <QSystemTrayIcon>
#include <functional>

class MenuBar : public QWidget {
  Q_OBJECT

 public:
  explicit MenuBar(QWidget* parent = nullptr) : QWidget(parent) {
    QMenu* aboutMenu = new QMenu(this);
    aboutMenu->setTitle("About");
    aboutMenu->addAction("Author");
    aboutMenu->addAction("License");

    QMenu* gMenu = new QMenu(this);
    gMenu->setTitle("Hello world!");

    switchAction_ = gMenu->addAction("Switch", [this]() {
      static bool flag = false;
      flag = !flag;
      if (flag) {
        this->switchAction_->setIcon(QIcon(":/icons/circle_green.svg"));
      } else {
        this->switchAction_->setIcon(QIcon(":/icons/circle_red.svg"));
      }
    });
    switchAction_->setIcon(QIcon(":/icons/circle_gray.svg"));

    gMenu->addMenu(aboutMenu);
    gMenu->addSeparator();
    gMenu->addAction("Exit", []() { QApplication::quit(); });

    QSystemTrayIcon* tray = new QSystemTrayIcon(QIcon::fromTheme(":/icons/menu.png"), this);
    tray->setContextMenu(gMenu);
    tray->show();
  }

  ~MenuBar() override = default;

 private:
  QAction* switchAction_;
};
