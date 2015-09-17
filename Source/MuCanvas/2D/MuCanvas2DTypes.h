#ifndef Mural_MuCanvas2DTypes_h
#define Mural_MuCanvas2DTypes_h

#include <glm/glm.hpp>

namespace mural {

  typedef union {
    struct {
      unsigned char r, g, b, a;
    } rgba;
    unsigned char components[4];
    unsigned int hex;
  } MuColorRGBA;

  struct MuVertex {
    glm::vec2 pos;
    glm::vec2 uv;
    MuColorRGBA color;
  };

}

#endif
