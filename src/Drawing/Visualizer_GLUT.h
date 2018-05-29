#pragma once

#include <map>
#include <set>

#include "Common.h"
#include "Trajectory.h"
#include "DataSource.h"
#include "Math/Geometry.h"
#include "Drawing/DrawingFuncs.h"
#include "Controller/VehicleDatatypes.h"
#include "Drawing/GLUTMenu.h"
#include "Utility/Camera.h"

using namespace std;

class QuadDynamics;
class GraphManager;

class Visualizer_GLUT : public DataSource
{

public:
  Visualizer_GLUT(int *argcp, char **argv);
  ~Visualizer_GLUT();

  void OnLoadScenario(string scenario);
  void Reset();
  void OnMouseClick(int button, int state, int x, int y);
  void OnMouseDoubleLClick(int x, int y);
  void OnMouseMove(int x, int y);
  void SetKeyboardFunc(void(*callback)(unsigned char, int, int));
  void OnResize(int width, int height);
  void Paint();
  void Update(float _simTime);
  bool IsKeyDown(uint8_t key);
  bool IsSpecialKeyDown(int specialKey);
  void SetArrow(V3F begin, V3F end)
  {
    _arrowBegin = begin;
    _arrowEnd = end;
  }
  void VisualizeQuadCopter(shared_ptr<QuadDynamics> quad);
  void VisualizeTrajectory(const Trajectory& traj,
                           bool drawPoints,
                           V3F color, 
                           float alpha=1, 
                           V3F pointColor=V3F(.1f,.2f,1),
                           V3F curPointColor=V3F(1,0,0),
                           V3F offset=V3F(), 
                           int style=0);
  void InitializeMenu(const vector<string>& strings);
  void OnMenu(string);

  vector<shared_ptr<QuadDynamics> > quads;
  shared_ptr<GraphManager> graph;
  GLUTMenu _menu;
  bool _exiting;

protected:
  void initializeGL(int *argcp, char **argv);
  shared_ptr<SLR::OpenGLDrawer> _glDraw;
  int _glutWindowNum;

private:
  string _cameraTrackingMode;
  GLuint MakeVolumeCallList();
  GLuint _volumeCallList;	
  Camera _camera;
  Timer _start;
  V3F _arrowBegin, _arrowEnd;
  GLdouble modelMatrix[16],projMatrix[16];
  GLint viewport[4];
  bool _mouseLeftDown, _mouseRightDown, _mouseMiddleDown;

protected:
  GLUquadricObj *glQuadric;
  bool _drawVolumeBoundaries;
  V3F _bgColorBottomRight, _bgColorBottomLeft, _bgColorTopRight, _bgColorTopLeft;
  V3D _refLoc;
  Timer _timeSinceLastPaint;
	
  void DrawBackground();
  void DrawCoordinateReference();
  void DrawBottomStatus(float simTime);
  void Draw(shared_ptr<QuadDynamics> quad);
  void DrawTrajectories(shared_ptr<QuadDynamics> quad);
	

public:
  bool showPropCommands;
  bool showRefTrajectory, showActualTrajectory;
  bool paused;
  // data source functions
  virtual bool GetData(const string& name, float& ret) const;
  virtual vector<string> GetFields() const;
  void OnMainTimer();

protected:
  SLR::LineD ScreenToPickVector(double x, double y);
  V3D _doubleClickMousePoint;
  Timer _doubleClickTimer;
  bool _objectSelected;
  int _selectedObjectIndex;
  V3F _selectedObjectPos;	
  LowPassFilter<V3D> _selectedObjectPos_filtered;
  Timer _lastDraw, _lastMainTimerEvent;
  float _draw_dt_ms, _timer_dt_ms, _last_draw_time_ms;
  // mouse
  int lastPosX, lastPosY;
  string _delayedScenarioLoader;
  float _lastSimTime;
  string _scenarioName;
};

