xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 152;
 -54.41095;291.91833;-43.09055;,
 -21.29250;297.27789;-46.86465;,
 -21.49840;263.94666;-47.07055;,
 -54.61670;264.12741;-43.29630;,
 11.82590;283.43134;-50.63875;,
 11.62005;263.76556;-50.84450;,
 44.94420;284.82159;-54.41280;,
 44.73840;263.58444;-54.61860;,
 -21.70410;230.61455;-47.27620;,
 -54.82260;230.79575;-43.50215;,
 11.41435;230.43350;-51.05025;,
 44.53280;230.25246;-54.82425;,
 -21.90980;197.28275;-47.48195;,
 -55.02825;197.46375;-43.70790;,
 11.20865;197.10155;-51.25590;,
 44.32705;196.92050;-55.02995;,
 -22.11555;163.95070;-47.68765;,
 -55.23395;164.13170;-43.91355;,
 11.00300;163.76945;-51.46160;,
 44.12140;163.58846;-55.23565;,
 -22.32120;130.61861;-47.89330;,
 -55.43960;130.79970;-44.11920;,
 10.79730;130.43755;-51.66730;,
 43.91575;130.25645;-55.44135;,
 -22.52690;97.28660;-48.09900;,
 -55.64530;97.46770;-44.32495;,
 10.59160;97.10550;-51.87300;,
 43.71005;96.92440;-55.64700;,
 -22.73255;63.95455;-48.30470;,
 -55.85105;64.13565;-44.53065;,
 10.38590;63.77350;-52.07865;,
 43.50430;63.59240;-55.85270;,
 -22.93820;30.62255;-48.51035;,
 -56.05670;30.80360;-44.73630;,
 10.18020;30.44150;-52.28435;,
 43.29865;30.26040;-56.05840;,
 -23.14395;-2.70945;-48.71605;,
 -56.26235;-2.52845;-44.94200;,
 9.97455;-2.89060;-52.49005;,
 43.09300;-3.07160;-56.26405;,
 48.71690;284.78116;-21.29455;,
 48.51115;263.35684;-21.50025;,
 52.48955;283.83511;11.82375;,
 52.28380;263.12921;11.61800;,
 56.26230;296.23318;44.94205;,
 56.05660;262.90146;44.73640;,
 48.30545;230.02490;-21.70595;,
 52.07815;229.79720;11.41235;,
 55.85090;229.56955;44.53070;,
 48.09980;196.69290;-21.91165;,
 51.87250;196.46515;11.20665;,
 55.64525;196.23755;44.32500;,
 47.89405;163.36079;-22.11735;,
 51.66675;163.13319;11.00100;,
 55.43965;162.90546;44.11940;,
 47.68840;130.02879;-22.32305;,
 51.46110;129.80115;10.79530;,
 55.23390;129.57350;43.91370;,
 47.48270;96.69680;-22.52870;,
 51.25540;96.46915;10.58960;,
 55.02820;96.24145;43.70800;,
 47.27700;63.36475;-22.73440;,
 51.04970;63.13710;10.38390;,
 54.82255;62.90940;43.50230;,
 47.07135;30.03270;-22.94005;,
 50.84405;29.80515;10.17825;,
 54.61685;29.57735;43.29665;,
 46.86560;-3.29915;-23.14580;,
 50.63840;-3.52690;9.97260;,
 54.41120;-3.75455;43.09095;,
 23.14390;296.41422;48.71610;,
 22.93815;263.08270;48.51030;,
 -9.97460;304.03024;52.49005;,
 -10.18035;263.26379;52.28430;,
 -43.09305;304.21136;56.26415;,
 -43.29880;263.44479;56.05835;,
 22.73250;229.75066;48.30470;,
 -10.38600;229.93175;52.07865;,
 -43.50455;230.11279;55.85270;,
 22.52680;196.41855;48.09900;,
 -10.59170;196.59975;51.87295;,
 -43.71020;196.78065;55.64705;,
 22.32110;163.08659;47.89330;,
 -10.79735;163.26759;51.66725;,
 -43.91585;163.44875;55.44130;,
 22.11540;129.75459;47.68760;,
 -11.00305;129.93565;51.46160;,
 -44.12160;130.11681;55.23565;,
 21.90975;96.42255;47.48195;,
 -11.20875;96.60365;51.25590;,
 -44.32725;96.78470;55.02995;,
 21.70405;63.09055;47.27625;,
 -11.41445;63.27160;51.05020;,
 -44.53295;63.45270;54.82425;,
 21.49835;29.75850;47.07055;,
 -11.62010;29.93960;50.84455;,
 -44.73865;30.12065;54.61860;,
 21.29270;-3.57360;46.86490;,
 -11.82580;-3.39245;50.63885;,
 -44.94430;-3.21125;54.41285;,
 -46.86570;304.43854;23.14590;,
 -47.07150;263.67255;22.94010;,
 -50.63835;297.23129;-9.97235;,
 -50.84420;263.90021;-10.17825;,
 -47.27715;230.34039;22.73445;,
 -51.04985;230.56810;-10.38390;,
 -47.48290;197.00850;22.52865;,
 -51.25555;197.23610;-10.58960;,
 -47.68860;163.67645;22.32300;,
 -51.46130;163.90410;-10.79535;,
 -47.89425;130.34441;22.11730;,
 -51.66695;130.57201;-11.00100;,
 -48.09995;97.01235;21.91165;,
 -51.87265;97.24010;-11.20670;,
 -48.30565;63.68035;21.70595;,
 -52.07830;63.90795;-11.41235;,
 -48.51130;30.34830;21.50025;,
 -52.28400;30.57600;-11.61805;,
 -48.71700;-2.98370;21.29460;,
 -52.48970;-2.75615;-11.82375;,
 -43.09305;304.21136;56.26415;,
 -9.97460;304.03024;52.49005;,
 -13.74725;304.25781;19.37180;,
 -46.86570;304.43854;23.14590;,
 23.14390;296.41422;48.71610;,
 19.37120;296.64169;15.59775;,
 56.26230;296.23318;44.94205;,
 52.48955;283.83511;11.82375;,
 -17.51995;297.05051;-13.74650;,
 -50.63835;297.23129;-9.97235;,
 15.59850;285.49246;-17.52050;,
 48.71690;284.78116;-21.29455;,
 -21.29250;297.27789;-46.86465;,
 -54.41095;291.91833;-43.09055;,
 11.82590;283.43134;-50.63875;,
 44.94420;284.82159;-54.41280;,
 -48.71700;-2.98370;21.29460;,
 -15.59850;-3.16485;17.52055;,
 -11.82580;-3.39245;50.63885;,
 -44.94430;-3.21125;54.41285;,
 17.51995;-3.34580;13.74655;,
 21.29270;-3.57360;46.86490;,
 50.63840;-3.52690;9.97260;,
 54.41120;-3.75455;43.09095;,
 -52.48970;-2.75615;-11.82375;,
 -19.37120;-2.93715;-15.59775;,
 13.74725;-3.11825;-19.37175;,
 46.86560;-3.29915;-23.14580;,
 -56.26235;-2.52845;-44.94200;,
 -23.14395;-2.70945;-48.71605;,
 9.97455;-2.89060;-52.49005;,
 43.09300;-3.07160;-56.26405;;
 
 126;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;3,2,8,9;,
 4;2,5,10,8;,
 4;5,7,11,10;,
 4;9,8,12,13;,
 4;8,10,14,12;,
 4;10,11,15,14;,
 4;13,12,16,17;,
 4;12,14,18,16;,
 4;14,15,19,18;,
 4;17,16,20,21;,
 4;16,18,22,20;,
 4;18,19,23,22;,
 4;21,20,24,25;,
 4;20,22,26,24;,
 4;22,23,27,26;,
 4;25,24,28,29;,
 4;24,26,30,28;,
 4;26,27,31,30;,
 4;29,28,32,33;,
 4;28,30,34,32;,
 4;30,31,35,34;,
 4;33,32,36,37;,
 4;32,34,38,36;,
 4;34,35,39,38;,
 4;6,40,41,7;,
 4;40,42,43,41;,
 4;42,44,45,43;,
 4;7,41,46,11;,
 4;41,43,47,46;,
 4;43,45,48,47;,
 4;11,46,49,15;,
 4;46,47,50,49;,
 4;47,48,51,50;,
 4;15,49,52,19;,
 4;49,50,53,52;,
 4;50,51,54,53;,
 4;19,52,55,23;,
 4;52,53,56,55;,
 4;53,54,57,56;,
 4;23,55,58,27;,
 4;55,56,59,58;,
 4;56,57,60,59;,
 4;27,58,61,31;,
 4;58,59,62,61;,
 4;59,60,63,62;,
 4;31,61,64,35;,
 4;61,62,65,64;,
 4;62,63,66,65;,
 4;35,64,67,39;,
 4;64,65,68,67;,
 4;65,66,69,68;,
 4;44,70,71,45;,
 4;70,72,73,71;,
 4;72,74,75,73;,
 4;45,71,76,48;,
 4;71,73,77,76;,
 4;73,75,78,77;,
 4;48,76,79,51;,
 4;76,77,80,79;,
 4;77,78,81,80;,
 4;51,79,82,54;,
 4;79,80,83,82;,
 4;80,81,84,83;,
 4;54,82,85,57;,
 4;82,83,86,85;,
 4;83,84,87,86;,
 4;57,85,88,60;,
 4;85,86,89,88;,
 4;86,87,90,89;,
 4;60,88,91,63;,
 4;88,89,92,91;,
 4;89,90,93,92;,
 4;63,91,94,66;,
 4;91,92,95,94;,
 4;92,93,96,95;,
 4;66,94,97,69;,
 4;94,95,98,97;,
 4;95,96,99,98;,
 4;74,100,101,75;,
 4;100,102,103,101;,
 4;102,0,3,103;,
 4;75,101,104,78;,
 4;101,103,105,104;,
 4;103,3,9,105;,
 4;78,104,106,81;,
 4;104,105,107,106;,
 4;105,9,13,107;,
 4;81,106,108,84;,
 4;106,107,109,108;,
 4;107,13,17,109;,
 4;84,108,110,87;,
 4;108,109,111,110;,
 4;109,17,21,111;,
 4;87,110,112,90;,
 4;110,111,113,112;,
 4;111,21,25,113;,
 4;90,112,114,93;,
 4;112,113,115,114;,
 4;113,25,29,115;,
 4;93,114,116,96;,
 4;114,115,117,116;,
 4;115,29,33,117;,
 4;96,116,118,99;,
 4;116,117,119,118;,
 4;117,33,37,119;,
 4;120,121,122,123;,
 4;121,124,125,122;,
 4;124,126,127,125;,
 4;123,122,128,129;,
 4;122,125,130,128;,
 4;125,127,131,130;,
 4;129,128,132,133;,
 4;128,130,134,132;,
 4;130,131,135,134;,
 4;136,137,138,139;,
 4;137,140,141,138;,
 4;140,142,143,141;,
 4;144,145,137,136;,
 4;145,146,140,137;,
 4;146,147,142,140;,
 4;148,149,145,144;,
 4;149,150,146,145;,
 4;150,151,147,146;;
 
 MeshMaterialList {
  3;
  126;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "Data\\TEXTURE\\images.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "Data\\TEXTURE\\thumbnail.png";
   }
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  192;
  -0.113749;0.007518;-0.993481;,
  -0.112764;0.008359;-0.993587;,
  -0.112594;0.010177;-0.993589;,
  -0.113468;0.007175;-0.993516;,
  -0.112974;0.007595;-0.993569;,
  -0.112889;0.008503;-0.993571;,
  -0.113185;0.006832;-0.993550;,
  -0.113184;0.006831;-0.993551;,
  -0.113183;0.006830;-0.993551;,
  -0.113184;0.006830;-0.993551;,
  -0.113183;0.006830;-0.993551;,
  -0.113183;0.006830;-0.993551;,
  -0.113185;0.006829;-0.993551;,
  -0.113183;0.006829;-0.993551;,
  -0.113183;0.006830;-0.993551;,
  -0.113185;0.006829;-0.993551;,
  -0.113183;0.006829;-0.993551;,
  -0.113183;0.006830;-0.993551;,
  -0.113184;0.006830;-0.993551;,
  -0.113183;0.006830;-0.993551;,
  -0.113183;0.006829;-0.993551;,
  -0.113184;0.006829;-0.993551;,
  -0.113183;0.006829;-0.993551;,
  -0.113183;0.006829;-0.993551;,
  -0.113184;0.006829;-0.993551;,
  -0.113183;0.006829;-0.993551;,
  -0.113183;0.006829;-0.993551;,
  -0.113184;0.006830;-0.993551;,
  -0.113183;0.006830;-0.993551;,
  -0.113183;0.006829;-0.993551;,
  -0.113408;0.011154;-0.993486;,
  0.993527;-0.008546;-0.113272;,
  0.993590;-0.007849;-0.112768;,
  -0.113296;0.008992;-0.993521;,
  0.993542;-0.006989;-0.113246;,
  0.993573;-0.006640;-0.112994;,
  -0.113184;0.006830;-0.993551;,
  0.993555;-0.005432;-0.113219;,
  0.993555;-0.005432;-0.113220;,
  -0.113184;0.006830;-0.993551;,
  0.993555;-0.005433;-0.113219;,
  0.993555;-0.005432;-0.113220;,
  -0.113184;0.006830;-0.993551;,
  0.993555;-0.005432;-0.113219;,
  0.993555;-0.005433;-0.113221;,
  -0.113183;0.006830;-0.993551;,
  0.993555;-0.005432;-0.113218;,
  0.993555;-0.005432;-0.113221;,
  -0.113183;0.006829;-0.993551;,
  0.993555;-0.005433;-0.113219;,
  0.993555;-0.005433;-0.113221;,
  -0.113183;0.006830;-0.993551;,
  0.993555;-0.005432;-0.113219;,
  0.993555;-0.005432;-0.113221;,
  -0.113183;0.006829;-0.993551;,
  0.993555;-0.005432;-0.113219;,
  0.993555;-0.005432;-0.113221;,
  -0.113183;0.006829;-0.993551;,
  0.993555;-0.005433;-0.113219;,
  0.993555;-0.005432;-0.113221;,
  0.993660;-0.007097;-0.112206;,
  0.112874;-0.006519;0.993588;,
  0.112880;-0.005897;0.993591;,
  0.993608;-0.006265;-0.112714;,
  0.113028;-0.006673;0.993569;,
  0.113031;-0.006362;0.993571;,
  0.993555;-0.005432;-0.113221;,
  0.113181;-0.006829;0.993551;,
  0.113183;-0.006829;0.993551;,
  0.993555;-0.005432;-0.113221;,
  0.113181;-0.006829;0.993551;,
  0.113183;-0.006830;0.993551;,
  0.993555;-0.005432;-0.113223;,
  0.113181;-0.006829;0.993551;,
  0.113183;-0.006830;0.993551;,
  0.993555;-0.005433;-0.113222;,
  0.113181;-0.006829;0.993551;,
  0.113183;-0.006829;0.993551;,
  0.993555;-0.005432;-0.113222;,
  0.113181;-0.006829;0.993551;,
  0.113182;-0.006830;0.993551;,
  0.993555;-0.005432;-0.113222;,
  0.113181;-0.006829;0.993551;,
  0.113182;-0.006829;0.993551;,
  0.993555;-0.005432;-0.113222;,
  0.113181;-0.006829;0.993551;,
  0.113182;-0.006829;0.993551;,
  0.993555;-0.005431;-0.113222;,
  0.113181;-0.006829;0.993551;,
  0.113182;-0.006830;0.993551;,
  0.113192;-0.005586;0.993557;,
  -0.993588;0.004693;0.112967;,
  -0.993609;0.005462;0.112746;,
  0.113188;-0.006207;0.993554;,
  -0.993572;0.005063;0.113093;,
  -0.993582;0.005447;0.112982;,
  0.113184;-0.006829;0.993551;,
  -0.993555;0.005433;0.113218;,
  -0.993555;0.005433;0.113219;,
  0.113184;-0.006830;0.993551;,
  -0.993555;0.005433;0.113218;,
  -0.993555;0.005433;0.113219;,
  0.113184;-0.006830;0.993551;,
  -0.993555;0.005432;0.113219;,
  -0.993555;0.005432;0.113218;,
  0.113183;-0.006829;0.993551;,
  -0.993555;0.005432;0.113219;,
  -0.993555;0.005432;0.113218;,
  0.113184;-0.006830;0.993551;,
  -0.993555;0.005432;0.113219;,
  -0.993555;0.005433;0.113219;,
  0.113184;-0.006829;0.993551;,
  -0.993555;0.005432;0.113218;,
  -0.993555;0.005432;0.113219;,
  0.113183;-0.006829;0.993551;,
  -0.993555;0.005432;0.113218;,
  -0.993555;0.005432;0.113219;,
  0.113183;-0.006831;0.993551;,
  -0.993555;0.005432;0.113219;,
  -0.993555;0.005432;0.113219;,
  0.112919;0.985272;-0.128406;,
  0.197314;0.966842;-0.162123;,
  0.123329;0.979465;-0.159492;,
  0.188267;0.972661;-0.135967;,
  -0.006171;-0.999962;-0.006170;,
  -0.006169;-0.999962;-0.006172;,
  -0.006170;-0.999962;-0.006171;,
  -0.006169;-0.999962;-0.006170;,
  0.993534;-0.008493;-0.113215;,
  0.993546;-0.006962;-0.113217;,
  0.993555;-0.005432;-0.113219;,
  0.993555;-0.005433;-0.113219;,
  0.993555;-0.005432;-0.113218;,
  0.993555;-0.005432;-0.113218;,
  0.993555;-0.005433;-0.113218;,
  0.993555;-0.005432;-0.113219;,
  0.993555;-0.005432;-0.113218;,
  0.993555;-0.005433;-0.113218;,
  0.113182;-0.006831;0.993551;,
  0.113181;-0.006830;0.993551;,
  0.113182;-0.006829;0.993551;,
  0.113182;-0.006829;0.993551;,
  0.113180;-0.006829;0.993551;,
  0.113180;-0.006830;0.993551;,
  0.113180;-0.006829;0.993551;,
  0.113180;-0.006829;0.993551;,
  0.113180;-0.006829;0.993551;,
  0.113180;-0.006829;0.993551;,
  -0.993561;0.004444;0.113212;,
  -0.993558;0.004938;0.113215;,
  -0.993603;0.005980;0.112769;,
  -0.993579;0.005708;0.112993;,
  -0.993555;0.005433;0.113218;,
  -0.993555;0.005433;0.113219;,
  -0.993555;0.005432;0.113219;,
  -0.993555;0.005433;0.113219;,
  -0.993555;0.005432;0.113219;,
  -0.993555;0.005432;0.113218;,
  -0.993555;0.005432;0.113219;,
  -0.993555;0.005432;0.113218;,
  -0.993555;0.005432;0.113219;,
  -0.993555;0.005433;0.113219;,
  -0.993555;0.005432;0.113219;,
  -0.993555;0.005432;0.113220;,
  -0.993555;0.005432;0.113218;,
  -0.993555;0.005432;0.113219;,
  -0.993555;0.005432;0.113218;,
  -0.993555;0.005432;0.113218;,
  0.006165;0.999962;0.006163;,
  0.114803;0.993369;-0.006256;,
  -0.006287;0.994679;-0.102828;,
  0.190575;0.976359;-0.102002;,
  0.157573;0.970101;-0.184593;,
  0.163891;0.971399;-0.171822;,
  -0.051591;0.989005;-0.138589;,
  0.078846;0.992391;-0.094574;,
  0.136475;0.988362;-0.067191;,
  -0.084189;0.994281;-0.065712;,
  0.171480;0.984018;-0.047990;,
  -0.013500;0.999491;-0.028914;,
  -0.006172;-0.999962;-0.006169;,
  -0.006172;-0.999962;-0.006170;,
  -0.006173;-0.999962;-0.006168;,
  -0.006170;-0.999962;-0.006173;,
  -0.006169;-0.999962;-0.006172;,
  -0.006169;-0.999962;-0.006173;,
  -0.006169;-0.999962;-0.006171;,
  -0.006167;-0.999962;-0.006170;,
  -0.006168;-0.999962;-0.006172;,
  -0.006170;-0.999962;-0.006172;,
  -0.006169;-0.999962;-0.006170;,
  -0.006167;-0.999962;-0.006170;;
  126;
  4;0,1,4,3;,
  4;1,2,5,4;,
  4;2,30,33,5;,
  4;3,4,7,6;,
  4;4,5,8,7;,
  4;5,33,36,8;,
  4;6,7,10,9;,
  4;7,8,11,10;,
  4;8,36,39,11;,
  4;9,10,13,12;,
  4;10,11,14,13;,
  4;11,39,42,14;,
  4;12,13,16,15;,
  4;13,14,17,16;,
  4;14,42,45,17;,
  4;15,16,19,18;,
  4;16,17,20,19;,
  4;17,45,48,20;,
  4;18,19,22,21;,
  4;19,20,23,22;,
  4;20,48,51,23;,
  4;21,22,25,24;,
  4;22,23,26,25;,
  4;23,51,54,26;,
  4;24,25,28,27;,
  4;25,26,29,28;,
  4;26,54,57,29;,
  4;128,31,34,129;,
  4;31,32,35,34;,
  4;32,60,63,35;,
  4;129,34,37,130;,
  4;34,35,38,37;,
  4;35,63,66,38;,
  4;130,37,40,131;,
  4;37,38,41,40;,
  4;38,66,69,41;,
  4;131,40,43,132;,
  4;40,41,44,43;,
  4;41,69,72,44;,
  4;132,43,46,133;,
  4;43,44,47,46;,
  4;44,72,75,47;,
  4;133,46,49,134;,
  4;46,47,50,49;,
  4;47,75,78,50;,
  4;134,49,52,135;,
  4;49,50,53,52;,
  4;50,78,81,53;,
  4;135,52,55,136;,
  4;52,53,56,55;,
  4;53,81,84,56;,
  4;136,55,58,137;,
  4;55,56,59,58;,
  4;56,84,87,59;,
  4;138,61,64,139;,
  4;61,62,65,64;,
  4;62,90,93,65;,
  4;139,64,67,140;,
  4;64,65,68,67;,
  4;65,93,96,68;,
  4;140,67,70,141;,
  4;67,68,71,70;,
  4;68,96,99,71;,
  4;141,70,73,142;,
  4;70,71,74,73;,
  4;71,99,102,74;,
  4;142,73,76,143;,
  4;73,74,77,76;,
  4;74,102,105,77;,
  4;143,76,79,144;,
  4;76,77,80,79;,
  4;77,105,108,80;,
  4;144,79,82,145;,
  4;79,80,83,82;,
  4;80,108,111,83;,
  4;145,82,85,146;,
  4;82,83,86,85;,
  4;83,111,114,86;,
  4;146,85,88,147;,
  4;85,86,89,88;,
  4;86,114,117,89;,
  4;148,91,94,149;,
  4;91,92,95,94;,
  4;92,150,151,95;,
  4;149,94,97,152;,
  4;94,95,98,97;,
  4;95,151,153,98;,
  4;152,97,100,154;,
  4;97,98,101,100;,
  4;98,153,155,101;,
  4;154,100,103,156;,
  4;100,101,104,103;,
  4;101,155,157,104;,
  4;156,103,106,158;,
  4;103,104,107,106;,
  4;104,157,159,107;,
  4;158,106,109,160;,
  4;106,107,110,109;,
  4;107,159,161,110;,
  4;160,109,112,162;,
  4;109,110,113,112;,
  4;110,161,163,113;,
  4;162,112,115,164;,
  4;112,113,116,115;,
  4;113,163,165,116;,
  4;164,115,118,166;,
  4;115,116,119,118;,
  4;116,165,167,119;,
  4;168,169,120,170;,
  4;169,171,121,120;,
  4;171,172,173,121;,
  4;170,120,122,174;,
  4;120,121,123,122;,
  4;121,173,175,123;,
  4;174,122,176,177;,
  4;122,123,178,176;,
  4;123,175,179,178;,
  4;180,124,181,182;,
  4;124,125,183,181;,
  4;125,184,185,183;,
  4;186,126,124,180;,
  4;126,127,125,124;,
  4;127,187,184,125;,
  4;188,189,126,186;,
  4;189,190,127,126;,
  4;190,191,187,127;;
 }
 MeshTextureCoords {
  152;
  0.419950;-2.096950;,
  0.680820;-2.096950;,
  0.680820;-1.763620;,
  0.419950;-1.763620;,
  0.941690;-2.096950;,
  0.941690;-1.763620;,
  1.202560;-2.096950;,
  1.202560;-1.763620;,
  0.680820;-1.430280;,
  0.419950;-1.430280;,
  0.941690;-1.430280;,
  1.202560;-1.430280;,
  0.680820;-1.096950;,
  0.419950;-1.096950;,
  0.941690;-1.096950;,
  1.202560;-1.096950;,
  0.680820;-0.763620;,
  0.419950;-0.763620;,
  0.941690;-0.763620;,
  1.202560;-0.763620;,
  0.680820;-0.430280;,
  0.419950;-0.430280;,
  0.941690;-0.430280;,
  1.202560;-0.430280;,
  0.680820;-0.096950;,
  0.419950;-0.096950;,
  0.941690;-0.096950;,
  1.202560;-0.096950;,
  0.680820;0.236380;,
  0.419950;0.236380;,
  0.941690;0.236380;,
  1.202560;0.236380;,
  0.680820;0.569720;,
  0.419950;0.569720;,
  0.941690;0.569720;,
  1.202560;0.569720;,
  0.680820;0.903050;,
  0.419950;0.903050;,
  0.941690;0.903050;,
  1.202560;0.903050;,
  0.995060;-2.096950;,
  0.995060;-1.763620;,
  0.787550;-2.096950;,
  0.787550;-1.763620;,
  0.580050;-2.096950;,
  0.580050;-1.763620;,
  0.995060;-1.430280;,
  0.787550;-1.430280;,
  0.580050;-1.430280;,
  0.995060;-1.096950;,
  0.787550;-1.096950;,
  0.580050;-1.096950;,
  0.995060;-0.763620;,
  0.787550;-0.763620;,
  0.580050;-0.763620;,
  0.995060;-0.430280;,
  0.787550;-0.430280;,
  0.580050;-0.430280;,
  0.995060;-0.096950;,
  0.787550;-0.096950;,
  0.580050;-0.096950;,
  0.995060;0.236380;,
  0.787550;0.236380;,
  0.580050;0.236380;,
  0.995060;0.569720;,
  0.787550;0.569720;,
  0.580050;0.569720;,
  0.995060;0.903050;,
  0.787550;0.903050;,
  0.580050;0.903050;,
  0.319180;-2.096950;,
  0.319180;-1.763620;,
  0.058310;-2.096950;,
  0.058310;-1.763620;,
  -0.202560;-2.096950;,
  -0.202560;-1.763620;,
  0.319180;-1.430280;,
  0.058310;-1.430280;,
  -0.202560;-1.430280;,
  0.319180;-1.096950;,
  0.058310;-1.096950;,
  -0.202560;-1.096950;,
  0.319180;-0.763620;,
  0.058310;-0.763620;,
  -0.202560;-0.763620;,
  0.319180;-0.430280;,
  0.058310;-0.430280;,
  -0.202560;-0.430280;,
  0.319180;-0.096950;,
  0.058310;-0.096950;,
  -0.202560;-0.096950;,
  0.319180;0.236380;,
  0.058310;0.236380;,
  -0.202560;0.236380;,
  0.319180;0.569720;,
  0.058310;0.569720;,
  -0.202560;0.569720;,
  0.319180;0.903050;,
  0.058310;0.903050;,
  -0.202560;0.903050;,
  0.004940;-2.096950;,
  0.004940;-1.763620;,
  0.212450;-2.096950;,
  0.212450;-1.763620;,
  0.004940;-1.430280;,
  0.212450;-1.430280;,
  0.004940;-1.096950;,
  0.212450;-1.096950;,
  0.004940;-0.763620;,
  0.212450;-0.763620;,
  0.004940;-0.430280;,
  0.212450;-0.430280;,
  0.004940;-0.096950;,
  0.212450;-0.096950;,
  0.004940;0.236380;,
  0.212450;0.236380;,
  0.004940;0.569720;,
  0.212450;0.569720;,
  0.004940;0.903050;,
  0.212450;0.903050;,
  -0.202560;-1.457360;,
  0.058310;-1.293850;,
  0.265810;-1.499420;,
  0.004940;-1.662930;,
  0.319180;-1.130330;,
  0.526680;-1.335900;,
  0.580050;-0.966820;,
  0.787550;-1.172380;,
  0.473320;-1.704980;,
  0.212450;-1.868500;,
  0.734190;-1.541470;,
  0.995060;-1.377950;,
  0.680820;-1.910550;,
  0.419950;-2.074070;,
  0.941690;-1.747040;,
  1.202560;-1.583520;,
  0.000000;0.666670;,
  0.333330;0.666670;,
  0.333330;1.000000;,
  0.000000;1.000000;,
  0.666670;0.666670;,
  0.666670;1.000000;,
  1.000000;0.666670;,
  1.000000;1.000000;,
  0.000000;0.333330;,
  0.333330;0.333330;,
  0.666670;0.333330;,
  1.000000;0.333330;,
  0.000000;0.000000;,
  0.333330;0.000000;,
  0.666670;0.000000;,
  1.000000;0.000000;;
 }
}