#include "Renderer.h"

//////////////////////////////////////////////////////////////////////////
/// A program egy elfogadott Grafika 2. házi alapjan keszult.
/// Referenciakent hasznalhatod de a kameraosztaly valahol biztos hogy rossz! (forditva van a kep)
/// 
/// Written and directed by: Gazder Bence (Gazben)
/// Contact: bencegazder@gmail.com
//////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv) {

	Renderer::getInstance()->Init(argc, argv);

	return 0;
}