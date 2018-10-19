/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2011-2014 OpenFOAM Foundation
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

Class
    Foam::solidBodyMotionNNNFvMesh

Description
    Solid-body motion of the mesh specified by a run-time selectable
    motion function.

SourceFiles
    solidBodyMotionNNNFvMesh.C

\*---------------------------------------------------------------------------*/

#ifndef solidBodyMotionNNNFvMesh_H
#define solidBodyMotionNNNFvMesh_H

#include "dynamicFvMesh.H"
#include "dictionary.H"
#include "pointIOField.H"
#include "solidBodyMotionNNNFunction.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                   Class solidBodyMotionNNNFvMesh Declaration
\*---------------------------------------------------------------------------*/

class solidBodyMotionNNNFvMesh
:
    public dynamicFvMesh
{
    // Private data

        //- Dictionary of motion control parameters
        const dictionary dynamicMeshCoeffs_;

        //- The motion control function
        autoPtr<solidBodyMotionNNNFunction> SBMFPtr_;

        //- The reference points which are transformed
        pointIOField undisplacedPoints_;

        //- Points to move when cell zone is supplied
        labelList pointIDs_;

        //- Flag to indicate whether all cells should move
        bool moveAllCells_;

        //- Name of velocity field
        word UName_;


    // Private Member Functions

        //- Disallow default bitwise copy construct
        solidBodyMotionNNNFvMesh(const solidBodyMotionNNNFvMesh&);

        //- Disallow default bitwise assignment
        void operator=(const solidBodyMotionNNNFvMesh&);


public:

    //- Runtime type information
    TypeName("solidBodyMotionNNNFvMesh");


    // Constructors

        //- Construct from IOobject
        solidBodyMotionNNNFvMesh(const IOobject& io);


    //- Destructor
    ~solidBodyMotionNNNFvMesh();


    // Member Functions

        //- Update the mesh for both mesh motion and topology change
        virtual bool update();
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
