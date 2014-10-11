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
#include <cppcore/Container/TQueue.h>

#include "gtest/gtest.h"

using namespace CPPCore;

//-------------------------------------------------------------------------------------------------
///	@class		TQueueTest
///	@ingroup	UnitTest
///
///	@brief	The queue tests.
//-------------------------------------------------------------------------------------------------
class TQueueTest : public testing::Test {
public:
	//---------------------------------------------------------------------------------------------
	virtual void setUp() { 
		// empty
	}

	//---------------------------------------------------------------------------------------------
	virtual void tearDown()	{ 
		// empty
	}
};

//---------------------------------------------------------------------------------------------
TEST_F( TQueueTest, constructTest) {
    TQueue<float> f32Queue;
    EXPECT_TRUE( f32Queue.isEmpty() );

    TQueue<float> copy( f32Queue );
    EXPECT_EQ( copy, f32Queue );
    EXPECT_TRUE( copy.isEmpty() );
}

//---------------------------------------------------------------------------------------------
TEST_F( TQueueTest, enqueueDequeueTest ) {
	TQueue<float> f32Queue;
	bool hasItems = false;
    float val = 0.0f;

	f32Queue.enqueue( 0.0f );
	EXPECT_EQ( f32Queue.size(), 1 );
	EXPECT_TRUE( !f32Queue.isEmpty() );
	hasItems = f32Queue.dequeue( val );
	EXPECT_TRUE( !hasItems );
	EXPECT_EQ( 0.0f, val );

	f32Queue.enqueue( 0.0f );
	f32Queue.enqueue( 1.0f );
	f32Queue.enqueue( 2.0f );
	EXPECT_EQ( f32Queue.size(), 3 );

	hasItems = f32Queue.dequeue( val );
	EXPECT_EQ( val, 0.0f );
	EXPECT_TRUE( hasItems );
	EXPECT_EQ( f32Queue.size(), 2 );

	hasItems = f32Queue.dequeue( val );
	EXPECT_EQ( val, 1.0f );
	EXPECT_TRUE( hasItems );
	EXPECT_EQ( f32Queue.size(), 1 );

	hasItems = f32Queue.dequeue( val );
	EXPECT_EQ( val, 2.0f );
	EXPECT_EQ( f32Queue.size(), 0 );
	EXPECT_TRUE( !hasItems );
	EXPECT_TRUE( f32Queue.isEmpty() );
}

//---------------------------------------------------------------------------------------------
TEST_F( TQueueTest, sizeTest ) {
    TQueue<float> f32Queue;
	EXPECT_EQ( f32Queue.size(), 0 );

	f32Queue.enqueue( 0.0f );
	f32Queue.enqueue( 1.0f );
	f32Queue.enqueue( 2.0f );
	EXPECT_EQ( f32Queue.size(), 3 );

    float val;
	bool hasItems = f32Queue.dequeue( val );
	EXPECT_TRUE( hasItems );
	EXPECT_EQ( val, 0.0f );
	EXPECT_EQ( f32Queue.size(), 2 );
}

//---------------------------------------------------------------------------------------------
TEST_F( TQueueTest, clearTest )	{
    TQueue<float> f32Queue;

	f32Queue.enqueue( 0.0f );
	f32Queue.enqueue( 1.0f );
	f32Queue.enqueue( 2.0f );
	EXPECT_EQ( f32Queue.size(), 3 );

	f32Queue.clear();
	EXPECT_TRUE( f32Queue.isEmpty() );
	EXPECT_EQ( 0, f32Queue.size() );
}

//---------------------------------------------------------------------------------------------
