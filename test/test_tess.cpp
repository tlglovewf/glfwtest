#include <iostream>
#include <cstring>
#include <vector>
#include <glm/glm.hpp>
#include <geometry/tess/tesselator.h>

using namespace std;

typedef glm::vec2 vertex;

int main(int argc, char **argv)
{
    TESStesselator *tess = nullptr;
    TESSalloc ma = {0};

    // memset(&ma, 0 , sizeof(ma));

    int allocated = 0;
    ma.memalloc = [](void *userData, unsigned int size) ->void*{
        int* allocated = ( int*)userData;
        TESS_NOTUSED(userData);
        *allocated += (int)size;
        return malloc(size);
    };
    ma.memfree  = [](void *userData, void *ptr) ->void{
        TESS_NOTUSED(userData);
	    free(ptr);
    };
    ma.userData = &allocated;

    ma.extraVertices = 256; // realloc not provided , allow 256 extra vectices;

    tess = tessNewTess(&ma);
    if( tess == nullptr )
        return -1;
    tessSetOption(tess, TESS_CONSTRAINED_DELAUNAY_TRIANGULATION, 1);

    std::vector<vertex> pts;
    pts.push_back({0.0f, 0.0f});
    pts.push_back({1.0f, 0.0f});
    pts.push_back({1.0f, 1.0f});
    pts.push_back({0.0f, 1.0f});

    pts.push_back({0.3f, 0.0f});
    pts.push_back({0.6f, 0.0f});
    pts.push_back({0.5f, 0.6f});

    tessAddContour(tess, 2, &pts[0], sizeof(vertex), pts.size());

    constexpr int len = 3;

    if(!tessTesselate(tess, TESS_WINDING_ODD, TESS_POLYGONS, len, 2, 0))
        return -1;

    const float *verts = tessGetVertices(tess);
	const int   *vinds = tessGetVertexIndices(tess);
	const int   *elems = tessGetElements(tess);
	const int   nverts = tessGetVertexCount(tess);
	const int   nelems = tessGetElementCount(tess);
    
    for(int i = 0; i < nelems; ++i)
    {
        const int *p = &elems[i * len];
        std::cout << "----" << std::endl;
        for(int j = 0; j < len && p[j] != TESS_UNDEF ; ++j)
        {
            std::cout << verts[p[j]*2] << " " << verts[p[j]*2+1] << std::endl;
        }
    }

    if (tess) 
        tessDeleteTess(tess);
     
    return 0;
} 