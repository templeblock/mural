//
//  MuPath.hpp
//  ciEjecta
//
//  Created by Sean on 10/3/15.
//
//

#pragma once

#include <vector>
#include "MuCanvas2DTypes.hpp"

#define MU_PATH_RECURSION_LIMIT 8
#define MU_PATH_DISTANCE_EPSILON 1.0f
#define MU_PATH_COLLINEARITY_EPSILON FLT_EPSILON
#define MU_PATH_MIN_STEPS_FOR_CIRCLE 20.0f
#define MU_PATH_MAX_STEPS_FOR_CIRCLE 64.0f

namespace mural {

  using ci::vec2;
  using ci::ColorAf;
  using ci::PolyLine2f;

  enum MuPathPolygonTarget {
    kMuPathPolygonTargetColor,
    kMuPathPolygonTargetDepth
  };

  enum MuPathFillRule {
    kMuPathFillRuleNonZero,
    kMuPathFillRuleEvenOdd
  };

  // We're using the PolyLine to store paths
  typedef std::vector<PolyLine2f> path_t;

  class MuCanvasContext2D;
  class MuPath {
    public:
      MuAffineTransform transform = MuAffineTransform();
      MuPathFillRule fillRule = kMuPathFillRuleNonZero;

      MuPath();
      ~MuPath() {}

      void push(vec2 v);
      void reset();
      void close();
      void endSubPath();
      void moveTo(float x, float y);
      void lineTo(float x, float y);
      void bezierCurveTo(float cpx1, float cpy1, float cpx2, float cpy2, float x, float y, float scale);
      void recursiveBezier(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, int level);
      void quadraticCurveTo(float cpx, float cpy, float x, float y, float scale);
      void recursiveQuadratic(float x1, float y1, float x2, float y2, float x3, float y3, int level);
      void arcTo(float x1, float y1, float x2, float y2, float radius);
      void arc(float x, float y, float radius, float startAngle, float endAngle, bool antiClockwise);

      void drawPolygonsToContext(MuCanvasContext2D *context, MuPathPolygonTarget target);
      void drawLinesToContext(MuCanvasContext2D *context);

    private:
      vec2 currentPos, lastPushed;
      vec2 minPos, maxPos;
      unsigned int longestSubpath = 0;

      float distanceTolerance = 0.0f;

      PolyLine2f currentPath;
      path_t paths;

      void drawArcTo(MuCanvasContext2D *context, const vec2 &point, const vec2 &p1, const vec2 &p2, const ColorAf &color);
  };

}
