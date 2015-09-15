/*

Copyright 2013 RALI

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

*/  

#include "beamssf.h"
#include "linearssf.h"

namespace japa
{

// ------------------------------------------------------------------------ //
BeamSSF::BeamSSF( SolutionMarker& marker ) : m_marker( marker )
{}

// ------------------------------------------------------------------------ //
SearchSpace& BeamSSF::operator()( SearchSpace& searchspace )
{
    LinearSSF ssf( m_marker );

    ssf.addPassagePoint( searchspace.getLowerBoundX(), 
                         searchspace.getLowerBoundY() );
    
    ssf.addPassagePoint( searchspace.getUpperBoundX(), 
                         searchspace.getUpperBoundY() );

    ssf( searchspace );

    return searchspace;
}

}// namespace japa
