// Copyright 2021 The "MobileTimeTracker" project authors. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be
// found in the LICENSE file.

#pragma once

#include <memory>
#include <vector>

#include "app/activity.h"
#include "app/edit_activity_dialog.h"
#include "app/list_model_base.h"

namespace m_time_tracker {

class AppState;

class ActivitiesListModelBase: public ListModelBase<Activity> {
 public:
  friend class ListModelBase<Activity>;
  ActivitiesListModelBase(
      AppState* app_state,
      Gtk::Window* parent_window,
      Glib::RefPtr<Gtk::Builder> resource_builder) noexcept;
  Glib::RefPtr<Gtk::Widget> CreateRowFromObject(
      const Activity& a) noexcept override;

  using ListModelBase::SetContent;

 protected:
  virtual bool ShouldShowActivity(const Activity&) noexcept {
    return true;
  }

 private:
  void DeleteActivity(Activity::Id activity_id) noexcept;
  void EditActivity(Activity::Id activity_id) noexcept;

  std::vector<Activity> activities_;

  Gtk::Window* const parent_window_;
  Glib::RefPtr<Gtk::Builder> resource_builder_;
};

}  // namespace m_time_tracker
