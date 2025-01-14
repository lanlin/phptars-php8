<?php
use PHPUnit\Framework\TestCase;

require_once 'SimpleStruct.php';
require_once 'NestedStruct.php';

class TestTarsClient extends TestCase
{
    public $iVersion = 1;
    public $iRequestId = 1;
    public $servantName = 'test.test.test';
    public $funcName = 'example';
    public $cPacketType = 0;
    public $iMessageType = 0;
    public $iTimeout = 2;
    public $contexts = array('test' => 'testYong');
    public $statuses = array('test' => 'testStatus');

    public function testBool()
    {
        $bool = true;

        $buf = \TUPAPI::putBool('1', $bool, $this->iVersion);

        $encodeBufs[] = $buf;

        $requestBuf = \TUPAPI::encode($this->iVersion, $this->iRequestId, $this->servantName,
            $this->funcName, $this->cPacketType, $this->iMessageType, $this->iTimeout,
            $this->contexts, $this->statuses, $encodeBufs);

        $decodeRet = \TUPAPI::decodeReqPacket($requestBuf);

        $respBuf = $decodeRet['sBuffer'];

        $out = \TUPAPI::getBool('1', $respBuf, true, $this->iVersion);

        $this->assertEquals($bool, $out);
    }

    public function testDefaultBool()
    {
        $bool = false;

        $buf = \TUPAPI::putBool('1', $bool, $this->iVersion);

        $encodeBufs[] = $buf;

        $requestBuf = \TUPAPI::encode($this->iVersion, $this->iRequestId, $this->servantName,
            $this->funcName, $this->cPacketType, $this->iMessageType, $this->iTimeout,
            $this->contexts, $this->statuses, $encodeBufs);

        $decodeRet = \TUPAPI::decodeReqPacket($requestBuf);

        $respBuf = $decodeRet['sBuffer'];

        $out = \TUPAPI::getBool('2', $respBuf, false, $this->iVersion);

        $this->assertEquals($bool, $out);
    }

    public function testChar()
    {
        $char = 1;

        $buf = \TUPAPI::putChar('1', $char, $this->iVersion);

        $encodeBufs[] = $buf;

        $requestBuf = \TUPAPI::encode($this->iVersion, $this->iRequestId, $this->servantName,
            $this->funcName, $this->cPacketType, $this->iMessageType, $this->iTimeout,
            $this->contexts, $this->statuses, $encodeBufs);

        $decodeRet = \TUPAPI::decodeReqPacket($requestBuf);

        $respBuf = $decodeRet['sBuffer'];

        $out = \TUPAPI::getChar('1', $respBuf, true, $this->iVersion);

        $this->assertEquals(pack('h', $char), $out);
    }

    public function testDefaultChar()
    {
        $char = 0;

        $buf = \TUPAPI::putChar('1', $char, $this->iVersion);

        $encodeBufs[] = $buf;

        $requestBuf = \TUPAPI::encode($this->iVersion, $this->iRequestId, $this->servantName,
            $this->funcName, $this->cPacketType, $this->iMessageType, $this->iTimeout,
            $this->contexts, $this->statuses, $encodeBufs);

        $decodeRet = \TUPAPI::decodeReqPacket($requestBuf);

        $respBuf = $decodeRet['sBuffer'];

        $out = \TUPAPI::getChar('2', $respBuf, false, $this->iVersion);

        $this->assertEquals(pack('h', $char), $out);
    }

    public function testUInt8()
    {
        $uint8 = 255;

        $buf = \TUPAPI::putUInt8('1', $uint8, $this->iVersion);

        $encodeBufs[] = $buf;

        $requestBuf = \TUPAPI::encode($this->iVersion, $this->iRequestId, $this->servantName,
            $this->funcName, $this->cPacketType, $this->iMessageType, $this->iTimeout,
            $this->contexts, $this->statuses, $encodeBufs);

        $decodeRet = \TUPAPI::decodeReqPacket($requestBuf);

        $respBuf = $decodeRet['sBuffer'];

        $out = \TUPAPI::getUInt8('1', $respBuf, true, $this->iVersion);

        $this->assertEquals($uint8, $out);
    }

    public function testDefaultUInt8()
    {
        $uint8 = 0;

        $buf = \TUPAPI::putUInt8('1', $uint8, $this->iVersion);

        $encodeBufs[] = $buf;

        $requestBuf = \TUPAPI::encode($this->iVersion, $this->iRequestId, $this->servantName,
            $this->funcName, $this->cPacketType, $this->iMessageType, $this->iTimeout,
            $this->contexts, $this->statuses, $encodeBufs);

        $decodeRet = \TUPAPI::decodeReqPacket($requestBuf);

        $respBuf = $decodeRet['sBuffer'];

        $out = \TUPAPI::getUInt8('2', $respBuf, false, $this->iVersion);

        $this->assertEquals($uint8, $out);
    }

    public function testShort()
    {
        $short = 255;

        $buf = \TUPAPI::putShort('1', $short, $this->iVersion);

        $encodeBufs[] = $buf;

        $requestBuf = \TUPAPI::encode($this->iVersion, $this->iRequestId, $this->servantName,
            $this->funcName, $this->cPacketType, $this->iMessageType, $this->iTimeout,
            $this->contexts, $this->statuses, $encodeBufs);

        $decodeRet = \TUPAPI::decodeReqPacket($requestBuf);

        $respBuf = $decodeRet['sBuffer'];

        $out = \TUPAPI::getShort('1', $respBuf, true, $this->iVersion);

        $this->assertEquals($short, $out);
    }

    public function testDefaultShort()
    {
        $short = 0;

        $buf = \TUPAPI::putShort('1', $short, $this->iVersion);

        $encodeBufs[] = $buf;

        $requestBuf = \TUPAPI::encode($this->iVersion, $this->iRequestId, $this->servantName,
            $this->funcName, $this->cPacketType, $this->iMessageType, $this->iTimeout,
            $this->contexts, $this->statuses, $encodeBufs);

        $decodeRet = \TUPAPI::decodeReqPacket($requestBuf);

        $respBuf = $decodeRet['sBuffer'];

        $out = \TUPAPI::getShort('2', $respBuf, false, $this->iVersion);

        $this->assertEquals($short, $out);
    }

    public function testUInt16()
    {
        $uint16 = 255;

        $buf = \TUPAPI::putUInt16('1', $uint16, $this->iVersion);

        $encodeBufs[] = $buf;

        $requestBuf = \TUPAPI::encode($this->iVersion, $this->iRequestId, $this->servantName,
            $this->funcName, $this->cPacketType, $this->iMessageType, $this->iTimeout,
            $this->contexts, $this->statuses, $encodeBufs);

        $decodeRet = \TUPAPI::decodeReqPacket($requestBuf);

        $respBuf = $decodeRet['sBuffer'];

        $out = \TUPAPI::getUInt16('1', $respBuf, true, $this->iVersion);

        $this->assertEquals($uint16, $out);
    }

    public function testDefaultUInt16()
    {
        $uint16 = 0;

        $buf = \TUPAPI::putUInt16('1', $uint16, $this->iVersion);

        $encodeBufs[] = $buf;

        $requestBuf = \TUPAPI::encode($this->iVersion, $this->iRequestId, $this->servantName,
            $this->funcName, $this->cPacketType, $this->iMessageType, $this->iTimeout,
            $this->contexts, $this->statuses, $encodeBufs);

        $decodeRet = \TUPAPI::decodeReqPacket($requestBuf);

        $respBuf = $decodeRet['sBuffer'];

        $out = \TUPAPI::getUInt16('2', $respBuf, false, $this->iVersion);

        $this->assertEquals($uint16, $out);
    }

    public function testInt32()
    {
        $int32 = 255;

        $buf = \TUPAPI::putInt32('1', $int32, $this->iVersion);

        $encodeBufs[] = $buf;

        $requestBuf = \TUPAPI::encode($this->iVersion, $this->iRequestId, $this->servantName,
            $this->funcName, $this->cPacketType, $this->iMessageType, $this->iTimeout,
            $this->contexts, $this->statuses, $encodeBufs);

        $decodeRet = \TUPAPI::decodeReqPacket($requestBuf);

        $respBuf = $decodeRet['sBuffer'];

        $out = \TUPAPI::getInt32('1', $respBuf, true, $this->iVersion);

        $this->assertEquals($int32, $out);
    }

    public function testDefaultInt32()
    {
        $int32 = 0;

        $buf = \TUPAPI::putInt32('1', $int32, $this->iVersion);

        $encodeBufs[] = $buf;

        $requestBuf = \TUPAPI::encode($this->iVersion, $this->iRequestId, $this->servantName,
            $this->funcName, $this->cPacketType, $this->iMessageType, $this->iTimeout,
            $this->contexts, $this->statuses, $encodeBufs);

        $decodeRet = \TUPAPI::decodeReqPacket($requestBuf);

        $respBuf = $decodeRet['sBuffer'];

        $out = \TUPAPI::getInt32('2', $respBuf, false, $this->iVersion);

        $this->assertEquals($int32, $out);
    }

    public function testUInt32()
    {
        $uint32 = 255;

        $buf = \TUPAPI::putUInt32('1', $uint32, $this->iVersion);

        $encodeBufs[] = $buf;

        $requestBuf = \TUPAPI::encode($this->iVersion, $this->iRequestId, $this->servantName,
            $this->funcName, $this->cPacketType, $this->iMessageType, $this->iTimeout,
            $this->contexts, $this->statuses, $encodeBufs);

        $decodeRet = \TUPAPI::decodeReqPacket($requestBuf);

        $respBuf = $decodeRet['sBuffer'];

        $out = \TUPAPI::getUInt32('1', $respBuf, true, $this->iVersion);

        $this->assertEquals($uint32, $out);
    }

    public function testDefaultUInt32()
    {
        $uint32 = 0;

        $buf = \TUPAPI::putUInt32('1', $uint32, $this->iVersion);

        $encodeBufs[] = $buf;

        $requestBuf = \TUPAPI::encode($this->iVersion, $this->iRequestId, $this->servantName,
            $this->funcName, $this->cPacketType, $this->iMessageType, $this->iTimeout,
            $this->contexts, $this->statuses, $encodeBufs);

        $decodeRet = \TUPAPI::decodeReqPacket($requestBuf);

        $respBuf = $decodeRet['sBuffer'];

        $out = \TUPAPI::getUInt32('3', $respBuf, false, $this->iVersion);

        $this->assertEquals($uint32, $out);
    }

    public function testInt64()
    {
        $int64 = 1025458;

        $buf = \TUPAPI::putInt64('1', $int64, $this->iVersion);

        $encodeBufs[] = $buf;

        $requestBuf = \TUPAPI::encode($this->iVersion, $this->iRequestId, $this->servantName,
            $this->funcName, $this->cPacketType, $this->iMessageType, $this->iTimeout,
            $this->contexts, $this->statuses, $encodeBufs);

        $decodeRet = \TUPAPI::decodeReqPacket($requestBuf);

        $respBuf = $decodeRet['sBuffer'];

        $out = \TUPAPI::getInt64('1', $respBuf, true, $this->iVersion);

        $this->assertEquals($int64, $out);
    }

    public function testDefaultInt64()
    {
        $int64 = 0;

        $buf = \TUPAPI::putInt64('1', $int64, $this->iVersion);

        $encodeBufs[] = $buf;

        $requestBuf = \TUPAPI::encode($this->iVersion, $this->iRequestId, $this->servantName,
            $this->funcName, $this->cPacketType, $this->iMessageType, $this->iTimeout,
            $this->contexts, $this->statuses, $encodeBufs);

        $decodeRet = \TUPAPI::decodeReqPacket($requestBuf);

        $respBuf = $decodeRet['sBuffer'];

        $out = \TUPAPI::getInt64('3', $respBuf, false, $this->iVersion);

        $this->assertEquals($int64, $out);
    }

    public function testDouble()
    {
        $double = 1.225845125412365;

        $buf = \TUPAPI::putDouble('1', $double, $this->iVersion);

        $encodeBufs[] = $buf;

        $requestBuf = \TUPAPI::encode($this->iVersion, $this->iRequestId, $this->servantName,
            $this->funcName, $this->cPacketType, $this->iMessageType, $this->iTimeout,
            $this->contexts, $this->statuses, $encodeBufs);

        $decodeRet = \TUPAPI::decodeReqPacket($requestBuf);

        $respBuf = $decodeRet['sBuffer'];

        $out = \TUPAPI::getDouble('1', $respBuf, true, $this->iVersion);

        $this->assertEquals($double, $out);
    }

    public function testDefaultDouble()
    {
        $double = 0;

        $buf = \TUPAPI::putDouble('1', $double, $this->iVersion);

        $encodeBufs[] = $buf;

        $requestBuf = \TUPAPI::encode($this->iVersion, $this->iRequestId, $this->servantName,
            $this->funcName, $this->cPacketType, $this->iMessageType, $this->iTimeout,
            $this->contexts, $this->statuses, $encodeBufs);

        $decodeRet = \TUPAPI::decodeReqPacket($requestBuf);

        $respBuf = $decodeRet['sBuffer'];

        $out = \TUPAPI::getDouble('2', $respBuf, false, $this->iVersion);

        $this->assertEquals($double, $out);
    }

    public function testFloat()
    {
        $float = 3.141592;

        $buf = \TUPAPI::putFloat('1', $float, $this->iVersion);

        $encodeBufs[] = $buf;

        $requestBuf = \TUPAPI::encode($this->iVersion, $this->iRequestId, $this->servantName,
            $this->funcName, $this->cPacketType, $this->iMessageType, $this->iTimeout,
            $this->contexts, $this->statuses, $encodeBufs);

        $decodeRet = \TUPAPI::decodeReqPacket($requestBuf);

        $respBuf = $decodeRet['sBuffer'];

        $out = \TUPAPI::getFloat('1', $respBuf, true, $this->iVersion);

        $this->assertEqualsWithDelta((float) $float, (float) $out, 0.0000001);
    }

    public function testDefaultFloat()
    {
        $float = 0;

        $buf = \TUPAPI::putFloat('1', $float, $this->iVersion);

        $encodeBufs[] = $buf;

        $requestBuf = \TUPAPI::encode($this->iVersion, $this->iRequestId, $this->servantName,
            $this->funcName, $this->cPacketType, $this->iMessageType, $this->iTimeout,
            $this->contexts, $this->statuses, $encodeBufs);

        $decodeRet = \TUPAPI::decodeReqPacket($requestBuf);

        $respBuf = $decodeRet['sBuffer'];

        $out = \TUPAPI::getFloat('2', $respBuf, false, $this->iVersion);

        $this->assertEqualsWithDelta((float) $float, (float) $out, 0.0000001);
    }

    public function testString()
    {
        $string = 'test';

        $buf = \TUPAPI::putString('1', $string, $this->iVersion);

        $encodeBufs[] = $buf;

        $requestBuf = \TUPAPI::encode($this->iVersion, $this->iRequestId, $this->servantName,
            $this->funcName, $this->cPacketType, $this->iMessageType, $this->iTimeout,
            $this->contexts, $this->statuses, $encodeBufs);

        $decodeRet = \TUPAPI::decodeReqPacket($requestBuf);

        $respBuf = $decodeRet['sBuffer'];

        $out = \TUPAPI::getString('1', $respBuf, true, $this->iVersion);

        $this->assertEquals($string, $out);
    }

    public function testDefaultString()
    {
        $string = '';

        $buf = \TUPAPI::putString('1', $string, $this->iVersion);

        $encodeBufs[] = $buf;

        $requestBuf = \TUPAPI::encode($this->iVersion, $this->iRequestId, $this->servantName,
            $this->funcName, $this->cPacketType, $this->iMessageType, $this->iTimeout,
            $this->contexts, $this->statuses, $encodeBufs);

        $decodeRet = \TUPAPI::decodeReqPacket($requestBuf);

        $respBuf = $decodeRet['sBuffer'];

        $out = \TUPAPI::getString('2', $respBuf, false, $this->iVersion);

        $this->assertEquals($string, $out);
    }

    public function testSimpleVector()
    {
        $shorts = ['test1', 'test2'];
        $vector = new \TARS_Vector(\TARS::STRING);
        foreach ($shorts as $short) {
            $vector->pushBack($short);
        }

        $buf = \TUPAPI::putVector('1', $vector, $this->iVersion);

        $encodeBufs[] = $buf;

        $requestBuf = \TUPAPI::encode($this->iVersion, $this->iRequestId, $this->servantName,
            $this->funcName, $this->cPacketType, $this->iMessageType, $this->iTimeout,
            $this->contexts, $this->statuses, $encodeBufs);

        $decodeRet = \TUPAPI::decodeReqPacket($requestBuf);

        $respBuf = $decodeRet['sBuffer'];

        $v = new \TARS_Vector(\TARS::STRING);
        $out = \TUPAPI::getVector('1', $v, $respBuf, true, $this->iVersion);

        $this->assertEquals($shorts, $out);
    }

    public function testEmptyVector()
    {
        $vector = new \TARS_Vector(\TARS::STRING);

        $buf = \TUPAPI::putVector('1', $vector, $this->iVersion);

        $encodeBufs[] = $buf;

        $requestBuf = \TUPAPI::encode($this->iVersion, $this->iRequestId, $this->servantName,
            $this->funcName, $this->cPacketType, $this->iMessageType, $this->iTimeout,
            $this->contexts, $this->statuses, $encodeBufs);

        $decodeRet = \TUPAPI::decodeReqPacket($requestBuf);

        $respBuf = $decodeRet['sBuffer'];

        $vector = new \TARS_Vector(\TARS::STRING);
        $out = \TUPAPI::getVector('1', $vector, $respBuf, true, $this->iVersion);

        $this->assertEquals([], $out);
    }

    public function testDefaultVector()
    {
        $vector = new \TARS_Vector(\TARS::STRING);

        $buf = \TUPAPI::putVector('1', $vector, $this->iVersion);

        $encodeBufs[] = $buf;

        $requestBuf = \TUPAPI::encode($this->iVersion, $this->iRequestId, $this->servantName,
            $this->funcName, $this->cPacketType, $this->iMessageType, $this->iTimeout,
            $this->contexts, $this->statuses, $encodeBufs);

        $decodeRet = \TUPAPI::decodeReqPacket($requestBuf);

        $respBuf = $decodeRet['sBuffer'];

        $vector = new \TARS_Vector(\TARS::STRING);
        $out = \TUPAPI::getVector('1', $vector, $respBuf, false, $this->iVersion);

        $this->assertEquals([], $out);
    }

    public function testVectorChar()
    {
        $vector = new \TARS_Vector(\TARS::CHAR);
        $vector->pushBack('t');
        $vector->pushBack('a');

        $buf = \TUPAPI::putVector('1', $vector, $this->iVersion);

        $encodeBufs[] = $buf;

        $requestBuf = \TUPAPI::encode($this->iVersion, $this->iRequestId, $this->servantName,
            $this->funcName, $this->cPacketType, $this->iMessageType, $this->iTimeout,
            $this->contexts, $this->statuses, $encodeBufs);

        $decodeRet = \TUPAPI::decodeReqPacket($requestBuf);

        $respBuf = $decodeRet['sBuffer'];

        $v = new \TARS_Vector(\TARS::CHAR);
        $out = \TUPAPI::getVector('1', $v, $respBuf, false, $this->iVersion);

        $this->assertEquals('ta', $out);
    }

    public function testSimpleStruct()
    {
        $simpleStruct = new SimpleStruct();
        $simpleStruct->id = 1;
        $simpleStruct->count = 2;

        $buf = \TUPAPI::putStruct('1', $simpleStruct, $this->iVersion);

        $encodeBufs[] = $buf;

        $requestBuf = \TUPAPI::encode($this->iVersion, $this->iRequestId, $this->servantName,
            $this->funcName, $this->cPacketType, $this->iMessageType, $this->iTimeout,
            $this->contexts, $this->statuses, $encodeBufs);

        $decodeRet = \TUPAPI::decodeReqPacket($requestBuf);

        $respBuf = $decodeRet['sBuffer'];

        $outSimpleStruct = new SimpleStruct();
        $result = \TUPAPI::getStruct('1', $outSimpleStruct, $respBuf, true, $this->iVersion);
        $this->fromArray($result, $outSimpleStruct);

        $this->assertEquals($simpleStruct, $outSimpleStruct);
    }

    public function testDefaultStruct()
    {
        $simpleStruct = new SimpleStruct();
        $simpleStruct->id = 1;
        $simpleStruct->count = 2;

        $buf = \TUPAPI::putStruct('1', $simpleStruct, $this->iVersion);

        $encodeBufs[] = $buf;

        $requestBuf = \TUPAPI::encode($this->iVersion, $this->iRequestId, $this->servantName,
            $this->funcName, $this->cPacketType, $this->iMessageType, $this->iTimeout,
            $this->contexts, $this->statuses, $encodeBufs);

        $decodeRet = \TUPAPI::decodeReqPacket($requestBuf);

        $respBuf = $decodeRet['sBuffer'];

        $outSimpleStruct = new SimpleStruct();
        $result = \TUPAPI::getStruct('2', $outSimpleStruct, $respBuf, false, $this->iVersion);
        $this->fromArray($result, $outSimpleStruct);

        $this->assertEquals([], $result);
    }

    public function testComplicateVector()
    {
        $simpleStruct1 = new SimpleStruct();
        $simpleStruct1->id = 1;
        $simpleStruct1->count = 2;

        $simpleStruct2 = new SimpleStruct();
        $simpleStruct2->id = 2;
        $simpleStruct2->count = 4;

        $vector = new \TARS_Vector(new SimpleStruct());

        $vector->pushBack($simpleStruct1);
        $vector->pushBack($simpleStruct2);

        $buf = \TUPAPI::putVector('1', $vector, $this->iVersion);

        $encodeBufs[] = $buf;

        $requestBuf = \TUPAPI::encode($this->iVersion, $this->iRequestId, $this->servantName,
            $this->funcName, $this->cPacketType, $this->iMessageType, $this->iTimeout,
            $this->contexts, $this->statuses, $encodeBufs);

        $decodeRet = \TUPAPI::decodeReqPacket($requestBuf);

        $respBuf = $decodeRet['sBuffer'];

        $v = new \TARS_Vector(new SimpleStruct());
        $out = \TUPAPI::getVector('1', $v, $respBuf, true, $this->iVersion);

        $okData = [
            [
                'id' => 1,
                'count' => 2,
                'page' => 1,
            ],
            [
                'id' => 2,
                'count' => 4,
                'page' => 1,
            ],
        ];

        $this->assertEquals($okData, $out);
    }

    public function testComplicateStruct()
    {
        $simpleStruct1 = new SimpleStruct();
        $simpleStruct1->id = 1;
        $simpleStruct1->count = 2;

        $nestedStruct = new NestedStruct();
        $nestedStruct->structMap->pushBack(['test1' => $simpleStruct1]);
        $nestedStruct->structMap->pushBack(['test4' => $simpleStruct1]);

        $nestedStruct->structList->pushBack($simpleStruct1);
        $nestedStruct->structList->pushBack($simpleStruct1);

        $nestedStruct->nestedStruct = $simpleStruct1;

        $structList = new \TARS_Vector(new SimpleStruct());
        $structList->pushBack($simpleStruct1);

        $nestedStruct->ext->pushBack(['test2' => $structList]);
        $nestedStruct->ext->pushBack(['test3' => $structList]);

        $buf = \TUPAPI::putStruct('1', $nestedStruct, $this->iVersion);

        $encodeBufs[] = $buf;

        $requestBuf = \TUPAPI::encode($this->iVersion, $this->iRequestId, $this->servantName,
            $this->funcName, $this->cPacketType, $this->iMessageType, $this->iTimeout,
            $this->contexts, $this->statuses, $encodeBufs);

        $decodeRet = \TUPAPI::decodeReqPacket($requestBuf);

        $respBuf = $decodeRet['sBuffer'];

        $nestedStructOut = new NestedStruct();

        $result = \TUPAPI::getStruct('1', $nestedStructOut, $respBuf, true, $this->iVersion);
        $this->fromArray($result, $nestedStructOut);

        $this->assertEquals($simpleStruct1, $nestedStructOut->nestedStruct);
    }

    public function testSimpleMap()
    {
        $strings = [['test1' => 1], ['test2' => 2]];
        $map = new \TARS_Map(\TARS::STRING, \TARS::INT64);
        foreach ($strings as $string) {
            $map->pushBack($string);
        }

        $buf = \TUPAPI::putMap('1', $map, $this->iVersion);

        $encodeBufs['map'] = $buf;

        $requestBuf = \TUPAPI::encode($this->iVersion, $this->iRequestId, $this->servantName,
            $this->funcName, $this->cPacketType, $this->iMessageType, $this->iTimeout,
            $this->contexts, $this->statuses, $encodeBufs);

        $decodeRet = \TUPAPI::decodeReqPacket($requestBuf);

        $respBuf = $decodeRet['sBuffer'];

        $map = new \TARS_Map(\TARS::STRING, \TARS::INT64);
        $out = \TUPAPI::getMap('1', $map, $respBuf, true, $this->iVersion);

        $okData = ['test1' => 1, 'test2' => 2];

        $this->assertEquals($okData, $out);
    }

    public function testEmptyMap()
    {
        $map = new \TARS_Map(\TARS::STRING, \TARS::INT64);

        $buf = \TUPAPI::putMap(1, $map, $this->iVersion);

        $encodeBufs[] = $buf;

        $requestBuf = \TUPAPI::encode($this->iVersion, $this->iRequestId, $this->servantName,
            $this->funcName, $this->cPacketType, $this->iMessageType, $this->iTimeout,
            $this->contexts, $this->statuses, $encodeBufs);

        $decodeRet = \TUPAPI::decodeReqPacket($requestBuf);

        $respBuf = $decodeRet['sBuffer'];

        $map = new \TARS_Map(\TARS::STRING, \TARS::INT64);
        $out = \TUPAPI::getMap(1, $map, $respBuf, true, $this->iVersion);

        $this->assertEquals([], $out);
    }

    public function testDefaultMap()
    {
        $map = new \TARS_Map(\TARS::STRING, \TARS::INT64);

        $buf = \TUPAPI::putMap(1, $map, $this->iVersion);

        $encodeBufs[] = $buf;

        $requestBuf = \TUPAPI::encode($this->iVersion, $this->iRequestId, $this->servantName,
            $this->funcName, $this->cPacketType, $this->iMessageType, $this->iTimeout,
            $this->contexts, $this->statuses, $encodeBufs);

        $decodeRet = \TUPAPI::decodeReqPacket($requestBuf);

        $respBuf = $decodeRet['sBuffer'];

        $map = new \TARS_Map(\TARS::STRING, \TARS::INT64);
        $out = \TUPAPI::getMap(2, $map, $respBuf, false, $this->iVersion);

        $this->assertEquals([], $out);
    }

    public function testComplicateMap()
    {
        $simpleStruct1 = new SimpleStruct();
        $simpleStruct1->id = 1;
        $simpleStruct1->count = 2;

        $simpleStruct2 = new SimpleStruct();
        $simpleStruct2->id = 2;
        $simpleStruct2->count = 4;

        $map = new \TARS_Map(\TARS::STRING, new SimpleStruct());

        $map->pushBack(['test1' => $simpleStruct1]);
        $map->pushBack(['test2' => $simpleStruct2]);

        $buf = \TUPAPI::putMap(1, $map, $this->iVersion);

        $encodeBufs[] = $buf;

        $requestBuf = \TUPAPI::encode($this->iVersion, $this->iRequestId, $this->servantName,
            $this->funcName, $this->cPacketType, $this->iMessageType, $this->iTimeout,
            $this->contexts, $this->statuses, $encodeBufs);

        $decodeRet = \TUPAPI::decodeReqPacket($requestBuf);

        $respBuf = $decodeRet['sBuffer'];

        $m = new \TARS_Map(\TARS::STRING, new SimpleStruct());
        $out = \TUPAPI::getMap(1, $m, $respBuf, true, $this->iVersion);

        $okData = [
            'test1' => [
                    'id' => 1,
                    'count' => 2,
                    'page' => 1,
                ],
            'test2' => [
                    'id' => 2,
                    'count' => 4,
                    'page' => 1,
                ],
        ];

        $this->assertEquals($okData, $out);
    }

    public function fromArray($data, &$structObj)
    {
        if (!empty($data)) {
            foreach ($data as $key => $value) {
                if (method_exists($structObj, 'set'.ucfirst($key))) {
                    call_user_func_array([$this, 'set'.ucfirst($key)], [$value]);
                } elseif ($structObj->$key instanceof \TARS_Struct) {
                    $this->fromArray($value, $structObj->$key);
                } else {
                    $structObj->$key = $value;
                }
            }
        }
    }
}
