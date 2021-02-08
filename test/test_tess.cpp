#include <iostream>
#include <cstring>
#include <vector>
#include <geometry/tess/tesselator.h>

using namespace std;

struct vertrex
{
    float x;
    float y;
};


struct MemPool
{
	unsigned char* buf  = nullptr;
	unsigned int   cap ;
	unsigned int   size;
};

void* poolAlloc( void* userData, unsigned int size )
{
	struct MemPool* pool = (struct MemPool*)userData;
	size = (size+0x7) & ~0x7;
	if (pool->size + size < pool->cap)
	{
		unsigned char* ptr = pool->buf + pool->size;
		pool->size += size;
		return ptr;
	}
	printf("out of mem: %d < %d!\n", pool->size + size, pool->cap);
	return 0;
}

void poolFree( void* userData, void* ptr )
{
	// empty
	TESS_NOTUSED(userData);
	TESS_NOTUSED(ptr);
}

int main(int argc, char **argv)
{

    TESStesselator *tess = nullptr;
    TESSalloc ma;
    struct MemPool pool;

    pool.size = 0;
    uint8_t mem[1024 * 1024] = {0};
    pool.cap  = sizeof(mem);
    pool.buf  = mem;
    memset(&ma, 0 , sizeof(ma));
    ma.memalloc = poolAlloc;
    ma.memfree  = poolFree;
    ma.userData = (void*)&pool;
    ma.extraVertices = 256; // realloc not provided , allow 256 extra vectices;

    tess = tessNewTess(&ma);
    if( tess == nullptr )
        return -1;
    tessSetOption(tess, TESS_CONSTRAINED_DELAUNAY_TRIANGULATION, 1);

    std::vector<vertrex> pts;
    pts.push_back({0,0});
    pts.push_back({1,0});
    pts.push_back({1,1});

    tessAddContour(tess, 2, &pts[0], sizeof(vertrex), pts.size());

    if(!tessTesselate(tess, TESS_WINDING_ODD, TESS_POLYGONS, 3, 2, 0))
        return -1;

    const float *verts = tessGetVertices(tess);
	const int   *vinds = tessGetVertexIndices(tess);
	const int   *elems = tessGetElements(tess);
	const int   nverts = tessGetVertexCount(tess);
	const int   nelems = tessGetElementCount(tess);

    if (tess) tessDeleteTess(tess);
    std::cout << "hello world." << std::endl;
    return 0;
} 