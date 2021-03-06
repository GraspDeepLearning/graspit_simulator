/*********************************************************************
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2010, Willow Garage, Inc.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of the Willow Garage nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *********************************************************************/

#ifndef _GRASPCLUSTERINGTASK_H_
#define _GRASPCLUSTERINGTASK_H_

#include <graspit_dbase_tasks/dbTask.h>

class GraspitDBGrasp;

namespace dbase_grasp_planner {

//! Selects the representative grasps (i.e. cluster centers) from a list of grasps
/*! This task is meant to be used *after* a grasp planning task has already been 
  run for a given hand and object. It will then go through the list of existing grasps
  and cluster them - i.e., for each set of grasps that are "close" in a Euclidian sense
  it will select one to be marked as "cluster representative". The idea is that, 
  when executing grasps, you do not want to try dozens of grasps that are within a 
  few mm of each other, since if one will fail chances are all will fail. You can 
  thus choose just the "cluster reps" and use those.
  
  Works by selecting the best grasp from a list, then setting it as the
  representative grasp for all other grasps that are close to it. Then does this
  iteratively on the remaining grasps.

  Two grasps are deemed close based on the position and orientation of they define
  plus the gripper angle.

  Will set the "cluster_rep" property of ALL grasps in the list based on what it
  thinks, i.e. mark it "true" for all those it thinks should be cluster reps and
  "false" for all others. 
 */
class GraspClusteringTask : public graspit_dbase_tasks::DBTask {
 private:
  //! The record of the actual planning task
  db_planner::PlanningTaskRecord mPlanningTask;

  //! Returns true if two grasps are close enough to be clustered together
  bool clusterGrasps(const GraspitDBGrasp *g1, const GraspitDBGrasp *g2);
 public:
  //! Just a stub for now
  GraspClusteringTask(graspit_dbase_tasks::DBTaskDispatcher *disp, 
                      db_planner::DatabaseManager *mgr, 
                      db_planner::TaskRecord rec);

  //! Nothing to do here
  ~GraspClusteringTask(){}

  //! Actually does all the work
  virtual void start();
};

}

#endif
