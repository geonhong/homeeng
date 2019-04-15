/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) YEAR OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Application
    NAME

Description

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"
#define tab "\t"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{
    #include "setRootCase.H"
    #include "createTime.H"
	#include "createMesh.H"

	const polyBoundaryMesh& bMesh = mesh.boundaryMesh();

	forAll(bMesh, i)
	{
		const polyPatch& patch = bMesh[i];
		Info<< patch.index() << tab 
			<< patch.name() << tab 
			<< patch.type() 
			<< endl;

		if (patch.type() == "wall")
		{
			const vectorField& fC = patch.faceCentres();
			const vectorField& fA = patch.faceAreas();

			scalar sumA(0.0);
			vector sumAC(vector::zero);

			forAll(fC, fi)
			{
				scalar Area = mag(fA[fi]);
				sumA += Area;
				sumAC += Area*fC[fi];
			}

			vector CofM = sumAC/sumA;

			Info<< "Center of Mass: " << CofM << endl;
		}
	}

    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    Info<< nl << "ExecutionTime = " << runTime.elapsedCpuTime() << " s"
        << "  ClockTime = " << runTime.elapsedClockTime() << " s"
        << nl << endl;

    Info<< "End\n" << endl;

    return 0;
}


// ************************************************************************* //
