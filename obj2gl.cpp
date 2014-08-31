// obj2gl.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ObjFile.h"
#include "GLFile.h"



int wmain(int argc, wchar_t* argv[])
{
	try
	{
		if( argc != 3 )
		{
			throw swException(wstring_make() << "usage: input.obj output.gl" );
		}

		wstring InputFileName = argv[1];
		wstring OutputFileName = argv[2];

		TriMesh mesh;

		cout << endl << "Loading: " << toNarrowString(InputFileName.c_str()).c_str() << endl;
		ObjFile InputFile(InputFileName, mesh);

		cout << endl << "Writing: " << toNarrowString(OutputFileName.c_str()) << endl;
		GLFile OutputFile(OutputFileName, mesh);

		return EXIT_SUCCESS;
	}
	catch(swException& e)
	{
		cout << toNarrowString(e.What()) << endl;
	}
	catch(exception& e)
	{
		cout << e.what() << endl;
	}
	catch(...)
	{
		cout << "unknown exception" << endl;
	}

	return EXIT_FAILURE;
}
