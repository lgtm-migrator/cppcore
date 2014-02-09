/*
-------------------------------------------------------------------------------------------------
The MIT License (MIT)

Copyright (c) 2014 Kim Kulling

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
-------------------------------------------------------------------------------------------------
*/
#pragma once
#ifndef CE_INFRASTRUCTURE_CORE_VARIANT_H_INC
#define CE_INFRASTRUCTURE_CORE_VARIANT_H_INC

#include <cppcore/CPPCoreCommon.h>
#include <cppcore/Common/CString.h>

#include <string.h>
#include <cassert>

namespace CPPCore {

//-------------------------------------------------------------------------------------------------
///	@class		Variant
///	@ingroup	CPPCore
///	
///	@brief	This class can be used to store integer or float data with a dynamical binding. It 
///	stores the type information at the runtime instead of checking this to compile-time. So it is 
///	possible to pass integer or float arguments dynamically to arbitrary customers without changing 
///	the calling signature of the used interface.
///	If you are trying to get a float value even if the instance stores currently an integer value 
///	on a debug build an assertion will be thrown. On a release build it is possible to get values, 
///	but an error will be logged.
//-------------------------------------------------------------------------------------------------
class Variant {
public:
	///	@enum	Type
	///	@brief	This enum describes the variable type of the variant instance.
	enum Type {
		None,		///< Initialization value.
		Int,		///< Integer value.
		Int3,		///< Integer vector, 3 components.
		Int4,		///< Integer vector, 4 components.
		Float,		///< Float value.
		Float3,		///< Float vector, 3 components.
		Float4,		///< Float vector, 4 components.
		Float4x4,	///< Float matrix, 4 x 4 components.
		String,		///< String value.
        Boolean,    ///< Boolean type.
		MaxType		///< Upper limit.
	};

	///	@brief	The class default constructor.
	Variant();

	///	@brief	The class constructor with type information and data. A data buffer will be used to pass 
	///			the data. The size of the buffer will be check on runtime as well.
	///	@param	type		Type enumeration.
	///	@param	pData		Pointer to the data buffer.
	///	@param	numItems	Size of the data buffer.
	Variant( Type type, void *pData, ui32 numItems );
	
    /// @brief  The class constructor with a boolean value.
    /// @param  value       [in] The boolean value.
    explicit Variant( bool value );

	///	@brief	The class copy constructor.
	///	@param	other	[in] Other instance to copy from.
	Variant( const Variant &other );

	///	@brief	The class destructor.
	~Variant();

	///	@brief	Returns the type of the instance.
	///	@return	TYpe enum of the current dynamic type of the instance.
	Type getType() const;

	///	@brief	Sets a new integer value, old values will be released and destroyed.
	///	@param	val		[in] A new integer value.
	void setInt( i32 val );

	///	@brief	Returns the integer value of the instance.
	///	@return	The stored integer value will be returned.
	i32 getInt() const;
	
	///	@brief	Set a new integer vector, the old data will be released and destroyed.
	///	@param	val1	Component 1, integer.
	///	@param	val2	Component 2, integer.
	///	@param	val3	Component 3, integer.
	void setInt3( i32 val1, i32 val2, i32 val3 );
	
	///	@brief	Returns a pointer to the first element of the integer vector. You can access the 2
	///			following with the index operator for instance.
	///	@return	Pointer to the first component of th vector array.
	i32 *getInt3() const;

	///	@brief	Set a new integer vector, the old data will be released and destroyed.
	///	@param	val1	Component 1, integer.
	///	@param	val2	Component 2, integer.
	///	@param	val3	Component 3, integer.
	///	@param	val4	Component 3, integer.
	void setInt4( i32 val1, i32 val2, i32 val3, i32 val4 );

	///	@brief	Returns a pointer to the first element of the integer vector. You can access the 3
	///			following with the index operator for instance.
	///	@return	Pointer to the first component of th vector array.
	i32 *getInt4() const;

	///	@brief	Returns the float value of the instance.
	///	@param	val		A new float value.
	void setFloat( f32 val );
	
	///	@brief	Returns the float value of the instance.
	///	@return	The stored float value will be returned.
	f32 getFloat() const;

	///	@brief	Set a new float vector, the old data will be released and destroyed.
	///	@param	val1	Component 1, float.
	///	@param	val2	Component 2, float.
	///	@param	val3	Component 3, float.
	void setFloat3( f32 val1, f32 val2, f32 val3 );
	
	///	@brief	Returns a pointer to the first element of the float vector. You can access the 2
	///			following with the index operator for instance.
	///	@return	Pointer to the first component of th vector array.
	f32 *getFloat3() const;

	///	@brief	Set a new float vector, the old data will be released and destroyed.
	///	@param	val1	Component 1, float.
	///	@param	val2	Component 2, float.
	///	@param	val3	Component 3, float.
	///	@param	val4	Component 4, float.
	void setFloat4( f32 val1, f32 val2, f32 val3, f32 val4 );

	///	@brief	Returns a pointer to the first element of the float vector. You can access the 3
	///			following with the index operator for instance.
	///	@return	Pointer to the first component of th vector array.
	f32 *getFloat4() const;

	///	@brief	Assigns a new float 4x4 item.
	///	@param	pData	[in] A float pointer to the 4x4 buffer.
	void setFloat4x4( f32 *pData );
	
	///	@brief	Returns the pointer to the float 4x4 value.
	///	@return	A pointer showing to the 4x4 float item.
	f32 *getFloat4x4() const;

	///	@brief	Sets a string value.
	///	@param	rValue	The new string value.
	void setString( const CString &rValue );
	
	///	@brief	Returns a constant reference to the string value.
	///	@return	A pointer showing to the data buffer of the string.
	const c8 *getString() const;

    void setBool( bool value );
    bool getBool() const;

	///	@brief	Clears the variant data, type will set back to None.
	void clear();

	///	@brief	Operator implementations.
	bool operator == ( const Variant &rOther ) const;
	Variant &operator = ( const Variant &rOther );

protected:
	bool isValid( Type type, ui32 numItems ) const;
	void reserve( Type type, ui32 size );

private:
	Type m_Type;
	ui32 m_BufferSize;
	void *m_pData;
};

//-------------------------------------------------------------------------------------------------
inline 
Variant::Variant()
: m_Type( None )
, m_BufferSize( 0 )
, m_pData( nullptr ) {
	// empty
}

//-------------------------------------------------------------------------------------------------
inline
Variant::Variant( Type type, void *pData, ui32 numItems ) 
: m_Type( None )
, m_BufferSize( 0 )
, m_pData( nullptr ) {
	if ( isValid( type, numItems ) ) {
		ui32 size = 0;
		m_Type = type;
		if ( type == String ) {
			assert( nullptr != pData );
			CString str( (c8*) pData );
			setString( str );
		} else {
			reserve( type, size );
			::memcpy( m_pData, pData, m_BufferSize );
		}
	}
}

//-------------------------------------------------------------------------------------------------
inline
Variant::Variant( bool value )
: m_Type( Boolean )
, m_BufferSize( 0 )
, m_pData( nullptr )  {
    reserve( Boolean, 0 );
    ::memcpy( m_pData, &value, m_BufferSize );

}

//-------------------------------------------------------------------------------------------------
inline
Variant::Variant( const Variant &other ) 
: m_Type( None )
, m_BufferSize( 0 )
, m_pData( NULL ) {
	m_Type = other.m_Type;
	if ( String == m_Type ) {
		setString( other.getString() );
	} else {
		reserve( m_Type, 0 );
		::memcpy( m_pData, other.m_pData, m_BufferSize );
	}
}

//-------------------------------------------------------------------------------------------------
inline 
Variant::~Variant() {
	clear();
}

//-------------------------------------------------------------------------------------------------
inline
Variant::Type Variant::getType() const {
	return m_Type;
}

//-------------------------------------------------------------------------------------------------
inline 
void Variant::setInt( i32 val ) {
	clear();
	reserve( Int, 0 );
	::memcpy( m_pData, &val, sizeof( i32 ) );
}

//-------------------------------------------------------------------------------------------------
inline 
i32 Variant::getInt() const {
	assert( m_Type == Int );

	return ( *reinterpret_cast<i32*>( m_pData ) );
}

//-------------------------------------------------------------------------------------------------
inline 
void Variant::setInt3( i32 val1, i32 val2, i32 val3 ) {
	clear();
	reserve( Int3, 0 );
	i32 *ptr = reinterpret_cast<i32*>( m_pData );
	*ptr = val1;
	++ptr;
	*ptr = val2;
	++ptr;
	*ptr = val3;
}

//-------------------------------------------------------------------------------------------------
inline 
i32 *Variant::getInt3() const {
	assert( m_Type == Int3 );
	return ( reinterpret_cast<i32*>( m_pData ) );
}

//-------------------------------------------------------------------------------------------------
inline
void Variant::setInt4( i32 val1, i32 val2, i32 val3, i32 val4 ) {	
	clear();
	reserve( Int4, 0 );
	i32 *ptr = reinterpret_cast<i32*>( m_pData );
	*ptr = val1;
	++ptr;
	*ptr = val2;
	++ptr;
	*ptr = val3;
	++ptr;
	*ptr = val4;
}

//-------------------------------------------------------------------------------------------------
inline 
i32 *Variant::getInt4() const {
	assert( m_Type == Int4 );
	
	return ( reinterpret_cast<i32*>( m_pData ) );
}

//-------------------------------------------------------------------------------------------------
inline 
void Variant::setFloat( f32 val ) {
	clear();
	reserve( Float, 0 );
	::memcpy( m_pData, &val, sizeof( f32 ) );
}

//-------------------------------------------------------------------------------------------------
inline 
f32 Variant::getFloat() const {
	assert( m_Type == Float );
	return ( *reinterpret_cast<f32*>( m_pData ) );
}

//-------------------------------------------------------------------------------------------------
inline 
void Variant::setFloat3( f32 val1, f32 val2, f32 val3 ) {
	clear();
	reserve( Float3, 0 );
	f32 *ptr = reinterpret_cast<f32*>( m_pData );
	*ptr = val1;
	++ptr;
	*ptr = val2;
	++ptr;
	*ptr = val3;

}

//-------------------------------------------------------------------------------------------------
inline 
f32 *Variant::getFloat3() const {
    assert( m_Type == Float3 );
	return ( reinterpret_cast<f32*>( m_pData ) );
}

//-------------------------------------------------------------------------------------------------
inline 
void Variant::setFloat4( f32 val1, f32 val2, f32 val3, f32 val4 ) {
	clear();
	reserve( Float4, 0 );
	f32 *ptr = reinterpret_cast<f32*>( m_pData );
	*ptr = val1;
	++ptr;
	*ptr = val2;
	++ptr;
	*ptr = val3;
	++ptr;
	*ptr = val4;
}

//-------------------------------------------------------------------------------------------------
inline 
f32 *Variant::getFloat4() const {
	assert( m_Type == Float4 );
	return ( reinterpret_cast<f32*>( m_pData ) );
}

//-------------------------------------------------------------------------------------------------
inline 
void Variant::setFloat4x4( f32 *pData ) {
	clear();
	reserve( Float4x4, 0 );
    ::memcpy( m_pData, pData, sizeof( f32 ) * 16 );
}

//-------------------------------------------------------------------------------------------------
inline 
f32 *Variant::getFloat4x4() const {
    assert( m_Type == Float4x4 );
    return ( reinterpret_cast<f32*>( m_pData ) );
}

//-------------------------------------------------------------------------------------------------
inline 
void Variant::setString( const CString &str ) {
	clear();
	m_Type = String;
    m_pData = new c8[ str.size() + 1 ];
	memcpy( m_pData, str.c_str(), sizeof( c8 ) * str.size() );
    c8 *ptr = (c8* ) m_pData;
    ptr[ str.size() ] = '\0';
}
	
//-------------------------------------------------------------------------------------------------
inline 
const c8 *Variant::getString() const {
	assert( m_Type == String );
    return static_cast<c8*>( m_pData );
}

//-------------------------------------------------------------------------------------------------
inline 
void Variant::setBool(  bool value ) {
    clear();
    reserve( Boolean, 0 );
    ::memcpy( m_pData, &value, sizeof( bool ) );
}

//-------------------------------------------------------------------------------------------------
inline 
bool Variant::getBool() const {
    assert( Boolean == m_Type );

    return ( *reinterpret_cast<bool*>( m_pData ) );
}

//-------------------------------------------------------------------------------------------------
inline 
void Variant::clear() {
	if ( None == m_Type ) {
		return;
	}

	delete [] m_pData;
	m_pData = nullptr;
	m_Type = None;
}

//-------------------------------------------------------------------------------------------------
inline 
bool Variant::operator == ( const Variant &rOther ) const {
	if ( rOther.m_Type != m_Type ) {
		return false;
	}
	
	if ( rOther.m_BufferSize != m_BufferSize ) {
		return false;
	}

	if ( 0 != ::memcmp( rOther.m_pData, m_pData, m_BufferSize ) ) {
		return false;
	}
	
	return true;
}

//-------------------------------------------------------------------------------------------------
inline 
Variant &Variant::operator = ( const Variant &rOther ) {
	if ( !( rOther == *this ) )	{
		m_Type = rOther.m_Type;
		reserve( m_Type, 0 );
		::memcpy( m_pData, rOther.m_pData, m_BufferSize );
	}

	return *this;
}

//-------------------------------------------------------------------------------------------------
inline 
bool Variant::isValid( Type type, ui32 numItems ) const {
	bool res = false;
	if ( type == Int || type == Float )	{
		if ( 1 == numItems ) {
			res = true;
		}
	} else if ( type == Int3 || type == Float3 ) {
		if ( 3 == numItems ) {
			res = true;
		}
	} else if ( type == Int4 || type == Float4 ) {
		if ( 4 == numItems ) {
			res = true;
		}
	} else if ( type == String ) {
		if ( 0 != numItems ) {
			res = true;
		}
	} else if ( type == None ) {
		res = true;
	}
	
	return res;
}

//-------------------------------------------------------------------------------------------------
inline 
void Variant::reserve( Type type, ui32 size ) {
	if ( 0 == size ) {
		if ( type == Int3 ) {
			size = sizeof( i32 ) * 3;
        } else if ( type == Float3 ) {
			size = sizeof( f32 ) * 3;
        } else if ( type == Int4 ) {
			size = sizeof( i32 ) * 4;
        } else if ( type == Float4 ) {
			size = sizeof( f32 ) * 4;
        } else if ( type == Float4x4 ) {
			size = sizeof( f32 ) * 4 * 4;
        } else if ( type == Int ) {
			size = sizeof( i32 );
        } else if ( type == Float ) {
			size = sizeof( f32 );
        } else if ( type == Boolean ) {
            size = sizeof( bool );
        }
	}

	m_BufferSize = size;
	m_pData = new uc8[ size ];
	m_Type = type;
}

//-------------------------------------------------------------------------------------------------

} // Namespace CPPCore

#endif // CE_INFRASTRUCTURE_CORE_VARIANT_H_INC
