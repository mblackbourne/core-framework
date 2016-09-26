/*
 * This file is protected by Copyright. Please refer to the COPYRIGHT file
 * distributed with this source distribution.
 *
 * This file is part of REDHAWK core.
 *
 * REDHAWK core is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * REDHAWK core is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License
 * for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see http://www.gnu.org/licenses/.
 */
// Not copyrighted - public domain.
//
// This sample parser implementation was generated by CodeSynthesis XSD,
// an XML Schema to C++ data binding compiler. You may use it in your
// programs without any restrictions.
//
#include<iterator>
#include "prf-pimpl.h"
#include "ossie/debug.h"

// Unit_pimpl
//

using namespace prf;

CREATE_LOGGER(prf_parser)

void Unit_pimpl::
pre ()
{
}

std::string Unit_pimpl::
post_Unit ()
{
  const ::std::string& v (post_string ());

  return v;
}

// AccessType_pimpl
//

void AccessType_pimpl::
pre ()
{
}

::std::string AccessType_pimpl::
post_AccessType ()
{
  const ::std::string& v (post_string ());
  return v;
}

// IsComplex_pimpl
//

void IsComplex_pimpl::
pre ()
{
}

::std::string IsComplex_pimpl::
post_IsComplex ()
{
  const ::std::string& v (post_string ());
  return v;
}

// IsCommandLine_pimpl
//

void IsCommandLine_pimpl::
pre ()
{
}

::std::string IsCommandLine_pimpl::
post_IsCommandLine ()
{
  const ::std::string& v (post_string ());
  return v;
}

// IsOptional_pimpl
//

void IsOptional_pimpl::
pre ()
{
}

::std::string IsOptional_pimpl::
post_IsOptional ()
{
  const ::std::string& v (post_string ());
  return v;
}

// action_pimpl
//

void action_pimpl::
pre ()
{
}

void action_pimpl::
type (const ::std::string& type)
{
    _type = type;
}

::std::string action_pimpl::
post_action ()
{
  return _type;
}

// ActionType_pimpl
//

void ActionType_pimpl::
pre ()
{
}

std::string ActionType_pimpl::
post_ActionType ()
{
  const ::std::string& v (post_string ());
  return v;
}

// configurationKind_pimpl
//

void configurationKind_pimpl::
pre ()
{
    _kindtype = "configure";
}

void configurationKind_pimpl::
kindtype (const ::std::string& kindtype)
{
    _kindtype = kindtype;
}

std::string configurationKind_pimpl::
post_configurationKind ()
{
    return _kindtype;
}

// enumeration_pimpl
//

void enumeration_pimpl::
pre ()
{
}

void enumeration_pimpl::
label (const ::std::string& label)
{
}

void enumeration_pimpl::
value (const ::std::string& value)
{
}

::std::map<std::string, std::string>::value_type enumeration_pimpl::
post_enumeration ()
{
    return std::map<std::string, std::string>::value_type("", "");
}

// enumerations_pimpl
//

void enumerations_pimpl::
pre ()
{
}

void enumerations_pimpl::
enumeration (const ::std::map<std::string, std::string>::value_type& enumeration)
{
}

::std::map<std::string, std::string> enumerations_pimpl::
post_enumerations ()
{
    return std::map<std::string, std::string>();
}

// inputValue_pimpl
//

void inputValue_pimpl::
pre ()
{
}

void inputValue_pimpl::
simple (const ossie::Property* simple)
{
}

void inputValue_pimpl::
post_inputValue ()
{
}

// kind_pimpl
//

void kind_pimpl::
pre ()
{
    _type = "configure"; // The default is configure
}

void kind_pimpl::
kindtype (const ::std::string& type)
{
    _type = type;
}

std::string kind_pimpl::
post_kind ()
{
    return _type;
}

// PropertyConfigurationType_pimpl
//

void PropertyConfigurationType_pimpl::
pre ()
{
}

std::string PropertyConfigurationType_pimpl::
post_PropertyConfigurationType ()
{
  const ::std::string& v (post_string ());
  return v;
}

// StructPropertyConfigurationType_pimpl
//

void StructPropertyConfigurationType_pimpl::
pre ()
{
}

::std::string StructPropertyConfigurationType_pimpl::
post_StructPropertyConfigurationType ()
{
  return post_PropertyConfigurationType ();
}

// properties_pimpl
//

void properties_pimpl::
pre ()
{
    this->_prf.reset(new ossie::PRF());
}

void properties_pimpl::
description (const ::std::string& description)
{
}

void properties_pimpl::
simple (const ossie::SimpleProperty& simple)
{
    LOG_TRACE(prf_parser, "Adding simple property")
    assert(_prf.get() != 0);
    _prf->addProperty(simple.clone());
}

void properties_pimpl::
simplesequence (const ossie::SimpleSequenceProperty& simplesequence)
{
  LOG_TRACE(prf_parser, "Adding simple sequence property " << simplesequence.getID());
  assert(_prf.get() != 0);
  _prf->addProperty(simplesequence.clone());
}

void properties_pimpl::
test ()
{
}

void properties_pimpl::
struct_ (const ossie::StructProperty& struct_)
{
  LOG_TRACE(prf_parser, "Adding struct property " << struct_.getID());
  assert(_prf.get() != 0);
  _prf->addProperty(struct_.clone());
}

void properties_pimpl::
structsequence (const ossie::StructSequenceProperty& structsequence)
{
  LOG_TRACE(prf_parser, "Adding struct sequence property " << structsequence.getID());
  assert(_prf.get() != 0);
  _prf->addProperty(structsequence.clone());
}

std::auto_ptr<ossie::PRF> properties_pimpl::
post_properties ()
{
    LOG_TRACE(prf_parser, "properties post")
    return _prf;
}

// PropertyValueType_pimpl
//

void PropertyValueType_pimpl::
pre ()
{
}

std::string PropertyValueType_pimpl::
post_PropertyValueType ()
{
  const ::std::string& v (post_string ());

  return v;
}

// range_pimpl
//

void range_pimpl::
pre ()
{
}

void range_pimpl::
max (const ::std::string& max)
{
    range.second = max;
}

void range_pimpl::
min (const ::std::string& min)
{
    range.first = min;
}

::std::pair<std::string, std::string> range_pimpl::
post_range ()
{
    return range;
}

// resultValue_pimpl
//

void resultValue_pimpl::
pre ()
{
}

void resultValue_pimpl::
simple (const ossie::Property* simple)
{
}

void resultValue_pimpl::
post_resultValue ()
{
}

// simple_pimpl
//

void simple_pimpl::
pre ()
{
    _id      = "";
    _name    = "";
    _type    = "";
    _complex = "";
    _mode    = "";
    _action  = "";
    _optional = "";
    _commandline = "";
    _kinds.clear();
    _value.reset();

}

void simple_pimpl::
description (const ::std::string& description)
{
  
}

void simple_pimpl::
value (const ::std::string& value)
{
    LOG_TRACE(prf_parser, "simple_pimpl value " << value)
    _value = std::auto_ptr<std::string>(new std::string(value));
}

void simple_pimpl::
units ()
{
}

void simple_pimpl::
range (const ::std::vector<std::string>& range)
{
}

void simple_pimpl::
enumerations (const ::std::map<std::string, std::string>& enumerations)
{
}

void simple_pimpl::
kind (const ::std::string& kind)
{
    LOG_TRACE(prf_parser, "simple_pimpl kind " << kind)
    _kinds.push_back(kind);
}

void simple_pimpl::
action (const ::std::string& action)
{
    LOG_TRACE(prf_parser, "simple_pimpl action " << action)
    _action = action;
}

void simple_pimpl::
id (const ::std::string& id)
{
    LOG_TRACE(prf_parser, "simple_pimpl id " << id)
    _id = id;
}

void simple_pimpl::
mode (const ::std::string& mode)
{
    LOG_TRACE(prf_parser, "simple_pimpl mode " << mode)
    _mode = mode;
}

void simple_pimpl::
name (const ::std::string& name)
{
    LOG_TRACE(prf_parser, "simple_pimpl name " << name)
    _name = name;
}

void simple_pimpl::
type (const ::std::string& type)
{
    LOG_TRACE(prf_parser, "simple_pimpl type " << type)
    _type = type;
}

void simple_pimpl::
complex (const ::std::string& complex_)
{
    LOG_TRACE(prf_parser, "simple_pimpl complex " << complex_)
    _complex = complex_;
}

void simple_pimpl::
optional (const ::std::string& optional)
{
    LOG_TRACE(prf_parser, "simple_pimpl optional " << optional)
    _optional = optional;
}

void simple_pimpl::
commandline (const ::std::string& commandline)
{
    LOG_TRACE(prf_parser, "simple_pimpl _commandline " << _commandline)
    _commandline = commandline;
}

const ossie::SimpleProperty& simple_pimpl::
post_simple ()
{
  if (_value.get()  != 0) {
    LOG_TRACE(prf_parser, "simple_pimpl post " << _id << " " << _name << " " << _value->c_str());
      _prop = ossie::SimpleProperty(_id, _name, _type, _mode, _action, _kinds, _value.get(), _complex, _commandline, _optional);
  } else {
    LOG_TRACE(prf_parser, "simple_pimpl post " << _id << " " << _name << " None");
      _prop = ossie::SimpleProperty(_id, _name, _type, _mode, _action, _kinds, 0, _complex, _commandline, _optional);
  }
  return _prop;
}

// simpleRef_pimpl
//

void simpleRef_pimpl::
pre ()
{
  simple =  ossie::SimplePropertyRef();
}

void simpleRef_pimpl::
refid (const ::std::string& refid)
{
    simple._id = refid;
}

void simpleRef_pimpl::
value (const ::std::string& value)
{
    simple._value = value;
}

const ossie::SimplePropertyRef& simpleRef_pimpl::
post_simpleRef ()
{
    return simple;
}

// simpleSequenceRef_pimpl
//

void simpleSequenceRef_pimpl::
pre ()
{
  simplesequence._values.clear();
  simplesequence = ossie::SimpleSequencePropertyRef();
}

void simpleSequenceRef_pimpl::
refid (const ::std::string& refid)
{
    simplesequence._id = refid;
}

void simpleSequenceRef_pimpl::
values (const ::std::vector<std::string>& values)
{
  simplesequence._values = values;
}

const ossie::SimpleSequencePropertyRef& simpleSequenceRef_pimpl::
post_simpleSequenceRef ()
{
    return simplesequence;
}

// simpleSequence_pimpl
//

void simpleSequence_pimpl::
pre ()
{
    _id      = "";
    _name    = "";
    _type    = "";
    _complex = "";
    _mode    = "";
    _action  = "";
    _optional = "";

    _kinds.clear();
    _values.clear();
}

void simpleSequence_pimpl::
description (const ::std::string& description)
{
}

void simpleSequence_pimpl::
values (const ::std::vector<std::string>& values)
{
    std::string vals;
    for (unsigned i=0; i<values.size(); ++i) {
        vals += values[i] + " ";
    }
    LOG_TRACE(prf_parser, "simpleSequence_pimpl values " << vals)
    _values.clear();
    std::copy(values.begin(), values.end(), std::back_inserter(_values));
}

void simpleSequence_pimpl::
units ()
{
}

void simpleSequence_pimpl::
range (const ::std::vector<std::string>& range)
{
}

void simpleSequence_pimpl::
kind (const ::std::string& kind)
{
    LOG_TRACE(prf_parser, "simpleSequence_pimpl kind " << kind)
    _kinds.push_back(kind);
}

void simpleSequence_pimpl::
action (const ::std::string& action)
{
    LOG_TRACE(prf_parser, "simpleSequence_pimpl action " << action)
    _action = action;
}

void simpleSequence_pimpl::
id (const ::std::string& id)
{
    LOG_TRACE(prf_parser, "simpleSequence_pimpl id " << id)
    _id = id;
}

void simpleSequence_pimpl::
mode (const ::std::string& mode)
{
    LOG_TRACE(prf_parser, "simple_pimpl mode " << mode)
    _mode = mode;
}

void simpleSequence_pimpl::
name (const ::std::string& name)
{
    LOG_TRACE(prf_parser, "simpleSequence_pimpl name " << name)
    _name = name;
}

void simpleSequence_pimpl::
type (const ::std::string& type)
{
    LOG_TRACE(prf_parser, "simpleSequence_pimpl type " << type)
    _type = type;
}

void simpleSequence_pimpl::
complex (const ::std::string& complex_)
{
    LOG_TRACE(prf_parser, "simpleSequence_pimpl complex " << complex_)
    _complex = complex_;
}

void simpleSequence_pimpl::
optional (const ::std::string& optional)
{
    LOG_TRACE(prf_parser, "simpleSequence_pimpl optional " << optional)
    _optional = optional;
}

const ossie::SimpleSequenceProperty& simpleSequence_pimpl::
post_simpleSequence ()
{
  _prop = ossie::SimpleSequenceProperty(_id, 
                                             _name, 
                                             _type, 
                                             _mode, 
                                             _action, 
                                             _kinds, 
                                             _values,
                                             _complex,
					     _optional);

  return _prop;
}

// struct_pimpl
//

void struct_pimpl::
pre ()
{

    _id = "";
    _name = "";
    _type = "";
    _mode = "";
    _kinds.clear();
    _value.clear();
}

void struct_pimpl::
description (const ::std::string& desciption)
{
}

void struct_pimpl::
simple (const ossie::SimpleProperty& property)
{
   _value.push_back(const_cast<ossie::Property*>(property.clone()));
}

void struct_pimpl::
simplesequence (const ossie::SimpleSequenceProperty& property)
{
    _value.push_back(const_cast<ossie::Property*>(property.clone()));
}

void struct_pimpl::
configurationkind (const ::std::string& kind)
{
    _kinds.push_back(kind);
}

void struct_pimpl::
id (const ::std::string& id)
{
    _id = id;
}

void struct_pimpl::
mode (const ::std::string& mode)
{
    _mode = mode;
}

void struct_pimpl::
name (const ::std::string& name)
{
    _name = name;
}

const ossie::StructProperty& struct_pimpl::
post_struct ()
{
    LOG_TRACE(prf_parser, "struct_pimpl post " << _id << " " << _name);
    for (std::vector<std::string>::const_iterator ii = _kinds.begin(); ii != _kinds.end(); ++ii) {
        LOG_TRACE(prf_parser, "    kind " << *ii);
    }
    
    ossie::PropertyList::const_iterator i;
    for (i = _value.begin(); i != _value.end(); ++i) {
        LOG_TRACE(prf_parser, "    value " << *i)
    }

     _prop = ossie::StructProperty(_id, _name, _mode, _kinds, _value);
    return _prop;
}

// structSequence_pimpl
//

void structSequence_pimpl::
pre ()
{
    _id = "";
    _name = "";
    _type = "";
    _mode = "";
    _kinds.clear();
    _values.clear();
    _struct = ossie::StructProperty();  // resets internal values vector
}

void structSequence_pimpl::
description (const ::std::string& description)
{
}

void structSequence_pimpl::
struct_ (const ossie::StructProperty& structProp)
{
 _struct = structProp;
}

void structSequence_pimpl::
structvalue (const ossie::ComponentPropertyMap& value)
{
    std::vector<ossie::Property*> propValue;
    std::vector<ossie::Property*> rmprops;
    const std::vector<ossie::Property*>& defaults = _struct.getValue();
    for (std::vector<ossie::Property*>::const_iterator prop = defaults.begin(); prop != defaults.end(); ++prop) {
        const std::string id = (*prop)->getID();
        ossie::ComponentPropertyMap::const_iterator ii = value.find(id);
        if (ii != value.end()) {
          ossie::Property *p=NULL;
          if (dynamic_cast<const ossie::SimpleProperty*>(*prop) != NULL) {
		const ossie::SimpleProperty* simp = dynamic_cast<const ossie::SimpleProperty*>(*prop);
                std::string val = static_cast<const ossie::SimplePropertyRef *>(ii->second)->getValue();
                p = new ossie::SimpleProperty(id, 
                                              simp->getName(), 
                                              simp->getType(), 
                                              simp->getMode(), 
                                              simp->getAction(), 
                                              simp->getKinds(), 
                                              val, 
                                              simp->getComplex(),
                                              simp->getCommandLine(),
                                              simp->getOptional());
                  rmprops.push_back(p);
            
   	    } else if (dynamic_cast<const ossie::SimpleSequenceProperty*>(*prop) != NULL) {
                const ossie::SimpleSequenceProperty* simpseq = dynamic_cast<const ossie::SimpleSequenceProperty*>(*prop);
                std::vector<std::string> vals = static_cast<const ossie::SimpleSequencePropertyRef *>(ii->second)->getValues();
                p = new ossie::SimpleSequenceProperty(id,
                                                      simpseq->getName(),
                                                      simpseq->getType(),
                                                      simpseq->getMode(),
                                                      simpseq->getAction(),
                                                      simpseq->getKinds(),
                                                      vals,
                                                      simpseq->getComplex(),
                                                      simpseq->getOptional());
                rmprops.push_back(p);
            } else {
                p = *prop;
            }

            propValue.push_back(p);
	}
    }
    _values.push_back(ossie::StructProperty(_struct.getID(), _struct.getName(), _struct.getMode(), _struct.getKinds(), propValue));
    // clean up unused properties..
    for ( std::vector<ossie::Property *>::iterator i = rmprops.begin(); i != rmprops.end(); ++i) { if ( *i ) delete *i;  }
}

void structSequence_pimpl::
configurationkind (const ::std::string& kind)
{
    _kinds.push_back(kind);
}

void structSequence_pimpl::
id (const ::std::string& id)
{
    _id = id;
}

void structSequence_pimpl::
mode (const ::std::string& mode)
{
    _mode = mode;
}

void structSequence_pimpl::
name (const ::std::string& name)
{
    _name = name;
}

const ossie::StructSequenceProperty& structSequence_pimpl::
post_structSequence ()
{
    _prop = ossie::StructSequenceProperty(_id, _name, _mode, _struct, _kinds, _values);
    return _prop;
}

// structValue_pimpl
//

void structValue_pimpl::
pre ()
{
  _values.clear();
}

void structValue_pimpl::
simpleref (const ossie::SimplePropertyRef& simpleref)
{
  _values.insert(simpleref._id,std::auto_ptr<ossie::ComponentProperty>(simpleref.clone()) );
}

void structValue_pimpl::
simplesequenceref (const ossie::SimpleSequencePropertyRef& simplesequenceref)
{
  _values.insert(simplesequenceref._id,std::auto_ptr<ossie::ComponentProperty>(simplesequenceref.clone()) );
}

const ossie::ComponentPropertyMap& structValue_pimpl::
post_structValue ()
{
  return _values;
}

// test_pimpl
//

void test_pimpl::
pre ()
{
}

void test_pimpl::
description (const ::std::string& description)
{
}

void test_pimpl::
inputvalue ()
{
}

void test_pimpl::
resultvalue ()
{
}

void test_pimpl::
id (const ::std::string& id)
{
}

void test_pimpl::
post_test ()
{
}

// values_pimpl
//

void values_pimpl::
pre ()
{
    values.clear();
}

void values_pimpl::
value (const ::std::string& value)
{
    values.push_back(value);
}

::std::vector<std::string> values_pimpl::
post_values ()
{
  return values;
}