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


#include "searchspace.h"

namespace japa
{

// ------------------------------------------------------------------------ //
SearchSpace::Iterator::Iterator( SearchSpaceIterator* iterator ) 
        : m_iterator( iterator )
{}

// ------------------------------------------------------------------------ //
SearchSpace::Iterator::Iterator( const Iterator& copy ) 
        : m_iterator( copy.m_iterator -> clone() )
{}

// ------------------------------------------------------------------------ //
SearchSpace::Iterator::~Iterator()
{}

// ------------------------------------------------------------------------ //
bool SearchSpace::Iterator::hasNext() const
{
    return m_iterator -> hasNext();
}

// ------------------------------------------------------------------------ //
void SearchSpace::Iterator::next()
{
    m_iterator -> next();
}

// ------------------------------------------------------------------------ //
int SearchSpace::Iterator::x() const
{
    return m_iterator -> x();
}

// ------------------------------------------------------------------------ //
int SearchSpace::Iterator::y() const
{
    return m_iterator -> y();
}

}// namespace japa
