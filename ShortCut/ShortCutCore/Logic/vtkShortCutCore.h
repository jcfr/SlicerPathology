#ifndef VTKSHORTCUTCORE_H
#define VTKSHORTCUTCORE_H

#include "vtkSlicerShortCutCoreModuleLogicExport.h"
#include "vtkImageData.h"
#include "ShortCutCoreSegmenter.h"

#include <QProgressBar>
#include <QMainWindow>
#include <QStatusBar>
#include "qSlicerApplication.h"

const unsigned short SrcDimension = 2;
typedef float DistPixelType;											// float type pixel for cost function
typedef short SrcPixelType;
typedef unsigned char LabPixelType;

class VTK_SLICER_SHORTCUTCORE_MODULE_LOGIC_EXPORT vtkShortCutCore : public vtkObject
{
public:
  static vtkShortCutCore* New();
//  vtkTypeRevisionMacro(vtkFastGrowCutSeg,vtkObject);
  vtkTypeMacro(vtkShortCutCore,vtkObject);


  //set parameters of Quick TCGA segmenter
  vtkSetObjectMacro(SourceVol, vtkImageData);
  vtkSetObjectMacro(SeedVol, vtkImageData);
  vtkSetObjectMacro(SegVol, vtkImageData);
  vtkSetObjectMacro(SCROIVol, vtkImageData);
  vtkSetMacro(otsuRatio, float);
  vtkSetMacro(curvatureWeight, double);
  vtkSetMacro(sizeThld, float);
  vtkSetMacro(sizeUpperThld, float);
  vtkSetMacro(mpp, double);


  //vtkSetObjectMacro(OutputVol, vtkImageData);

//  vtkSetMacro(InitializationFlag, bool);

  //processing functions
  void Run_QTCGA_Segmentation();
  void Run_QTCGA_Template();
  void Run_Refine_Curvature();
  void Run_QTCGA_ShortCut();
  void Initialization();
//  void RunFGC();
  void PrintSelf(ostream &os, vtkIndent indent);

protected:
  vtkShortCutCore();
  virtual ~vtkShortCutCore();

private:
  //vtk image data (from slicer)
  vtkImageData* SourceVol;
  vtkImageData* SeedVol;
  vtkImageData* SegVol;
  vtkImageData* SCROIVol;

  float otsuRatio;
  double curvatureWeight;
  float sizeThld;
  float sizeUpperThld;
  double mpp;

  cv::Mat m_imSrc;
  cv::Mat m_imLab;
  cv::Mat m_imPreSeg;
  cv::Mat m_imSCROI;

  //logic code
  ShortCutCoreSegmenter* m_qTCGASeg;

  //state variables
  bool InitializationFlag;

};
#endif
