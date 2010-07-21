/************************************************************************
**
**  Copyright (C) 2010  Strahinja Markovic
**
**  This file is part of FlightCrew.
**
**  FlightCrew is free software: you can redistribute it and/or modify
**  it under the terms of the GNU Lesser General Public License as published
**  by the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**
**  FlightCrew is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU Lesser General Public License for more details.
**
**  You should have received a copy of the GNU Lesser General Public License
**  along with FlightCrew.  If not, see <http://www.gnu.org/licenses/>.
**
*************************************************************************/

#include <stdafx.h>
#include "TitlePresent.h"
#include "Result.h"
#include <ToXercesStringConverter.h>
#include <XmlUtils.h>

namespace xe = XercesExt;

std::vector<Result> TitlePresent::ValidateXml( const xc::DOMDocument &document )
{
    xc::DOMElement *root_element = document.getDocumentElement();
    xc::DOMNodeList *title_elements = root_element->getElementsByTagNameNS(
                                    X( "*" ),  X( "title" ) );

    std::vector<Result> results;

    if ( title_elements->getLength() < 1 )
    {
        xc::DOMNodeList *metadata_elements = root_element->getElementsByTagNameNS(
                                        X( "*" ),  X( "metadata" ) );

        if ( metadata_elements->getLength() == 1 )
        {
            xe::NodeLocationInfo node_location =
                    xe::GetNodeLocationInfo( *metadata_elements->item( 0 ) );

            results.push_back( Result( ERROR_OPF_NO_TITLE, node_location ) );
        }

        else
        {
            results.push_back( Result( ERROR_OPF_NO_TITLE ) );
        }
    }

    else
    {
        results.push_back( Result() );
    }

    return results;
}
