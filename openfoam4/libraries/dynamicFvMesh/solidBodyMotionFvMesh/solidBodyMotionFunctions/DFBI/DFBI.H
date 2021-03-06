/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2011-2013 OpenFOAM Foundation
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
    Foam::solidBodyMotionFunctions::DFBI

Description
    SolidBodyMotionFvMesh 6DoF motion function. Constant acceleration motion

SourceFiles
    DFBI.C

\*---------------------------------------------------------------------------*/

#ifndef DFBI_H
#define DFBI_H

#include "solidBodyMotionNNNFunction.H"
#include "primitiveFields.H"
#include "point.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace solidBodyMotionFunctions
{

class solidBodyMotionState
{
	scalar mass_;
	point initDispl_;
	point initPosition_;

	vector a_;
	vector v_;
	point x_;

	vector a0_;
	vector v0_;
	point x0_;

public:
	solidBodyMotionState
	(
		const vector& v,
		const vector& x
	)
	:
		a_(vector::zero),
		a0_(vector::zero),
		v_(v), x_(x),
		v0_(v), x0_(x)
	{}

	solidBodyMotionState
	(
		const dictionary& dict
	)
	:
		mass_(readScalar(dict.lookup("mass"))),
		initDispl_(dict.lookup("initialDisplacement")),
		initPosition_(dict.lookup("position")),
		a_(vector::zero),
		v_(dict.lookup("velocity")),
		x_(dict.lookup("position"))
	{
		this->update();
	}

	// Access
		const scalar& mass() const { return mass_; }
		const vector& initDispl() const { return initDispl_; }
		const vector& initPosition() const { return initPosition_; }
		const vector& v() const { return v_; }
		const point& x() const { return x_; }
		const vector& v0() const { return v0_; }
		const point& x0() const { return x0_; }

		scalar& mass() { return mass_; }
		vector& initDispl() { return initDispl_; }
		vector& initPosition() { return initPosition_; }
		vector& a() { return a_; }
		vector& v() { return v_; }
		point& x() { return x_; }

		vector& a0() { return a0_; }
		vector& v0() { return v0_; }
		point& x0() { return x0_; }

		void update()
		{
			a0_ = a_;
			v0_ = v_;
			x0_ = x_;
		}

		void update
		(
			const vector& a,
			const vector& v, 
			const point& x
		)
		{
			a0_ = a_;
			v0_ = v_;
			x0_ = x_;

			a_ = a;
			v_ = v;
			x_ = x;
		}
	
};

Ostream& operator<<
(
	Ostream& os,
	const solidBodyMotionState& s
)
{
	os	<< "DFBI Coefficients" << nl
		<< "{\n"
		<< "\tmass    \t" << s.mass() << nl
		<< "\tvelocity\t" << s.v() << nl
		<< "\tposition\t" << s.x() << nl
		<< "}" << endl;

	return os;
}

/*---------------------------------------------------------------------------*\
                          Class DFBI Declaration
\*---------------------------------------------------------------------------*/

class DFBI
:
    public solidBodyMotionNNNFunction
{
    // Private data

        //- Body motion state
		solidBodyMotionState s_;

		//- Relaxation factors
			// Acceleration
			scalar lambda_;

			// Velocity
			scalar gamma_;

			// Position
			scalar beta_;

		bool first_;

    // Private Member Functions

		//- Solve the motion equation
		void solve();

        //- Disallow copy construct
        DFBI(const DFBI&);

        //- Disallow default bitwise assignment
        void operator=(const DFBI&);


public:

    //- Runtime type information
    TypeName("DFBI");


    // Constructors

        //- Construct from components
        DFBI
        (
            const dictionary& SBMFCoeffs,
            const Time& runTime
        );

        //- Construct and return a clone
        virtual autoPtr<solidBodyMotionNNNFunction> clone() const
        {
            return autoPtr<solidBodyMotionNNNFunction>
            (
                new DFBI
                (
                    SBMFCoeffs_,
                    time_
                )
            );
        }


    //- Destructor
    virtual ~DFBI();


    // Member Functions

        //- Return the solid-body motion transformation septernion
        virtual septernion transformation();

        //- Update properties from given dictionary
        virtual bool read(const dictionary& SBMFCoeffs);
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace solidBodyMotionFunctions
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
