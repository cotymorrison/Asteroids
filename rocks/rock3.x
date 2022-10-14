xof 0303txt 0032


template VertexDuplicationIndices { 
 <b8d65549-d7c9-4995-89cf-53a9a8b031e3>
 DWORD nIndices;
 DWORD nOriginalVertices;
 array DWORD indices[nIndices];
}
template XSkinMeshHeader {
 <3cf169ce-ff7c-44ab-93c0-f78f62d172e2>
 WORD nMaxSkinWeightsPerVertex;
 WORD nMaxSkinWeightsPerFace;
 WORD nBones;
}
template SkinWeights {
 <6f0d123b-bad2-4167-a0d0-80224f25fabb>
 STRING transformNodeName;
 DWORD nWeights;
 array DWORD vertexIndices[nWeights];
 array float weights[nWeights];
 Matrix4x4 matrixOffset;
}

Frame RootFrame {

  FrameTransformMatrix {
    1.000000,0.000000,0.000000,0.000000,
    0.000000,1.000000,0.000000,0.000000,
    0.000000,0.000000,-1.000000,0.000000,
    0.000000,0.000000,0.000000,1.000000;;
  }
Frame Stone_Forest_1_LOD3 {

  FrameTransformMatrix {
    0.010000,0.000000,0.000000,0.000000,
    0.000000,0.010000,0.000000,0.000000,
    0.000000,0.000000,0.010000,0.000000,
    0.000000,0.000000,0.000000,1.000000;;
  }
Mesh {
150;
36.025700; -35.951600; -16.101700;,
-43.247200; -43.634600; -33.988800;,
0.014600; 0.016000; -42.080900;,
36.025700; -35.951600; -16.101700;,
0.014600; 0.016000; -42.080900;,
63.654800; 32.007700; -7.773900;,
0.014600; 0.016000; -42.080900;,
-43.247200; -43.634600; -33.988800;,
-41.390400; 41.060200; -27.017000;,
0.014600; 0.016000; -42.080900;,
-41.390400; 41.060200; -27.017000;,
63.654800; 32.007700; -7.773900;,
0.602000; 0.161600; 146.148800;,
-72.737900; 37.495500; 129.261700;,
-80.945400; -40.904400; 95.342400;,
-80.945400; -40.904400; 95.342400;,
-0.027500; -82.501200; 98.705800;,
0.602000; 0.161600; 146.148800;,
42.584500; -42.599700; 142.365800;,
0.602000; 0.161600; 146.148800;,
-0.027500; -82.501200; 98.705800;,
-72.737900; 37.495500; 129.261700;,
0.602000; 0.161600; 146.148800;,
0.741600; 63.171600; 119.733100;,
0.602000; 0.161600; 146.148800;,
42.584500; -42.599700; 142.365800;,
34.587400; 69.078200; 125.256100;,
34.587400; 69.078200; 125.256100;,
0.741600; 63.171600; 119.733100;,
0.602000; 0.161600; 146.148800;,
-43.247200; -43.634600; -33.988800;,
36.025700; -35.951600; -16.101700;,
0.007700; -84.077600; 13.618000;,
69.484800; -69.291600; 21.626400;,
0.007700; -84.077600; 13.618000;,
36.025700; -35.951600; -16.101700;,
-40.100000; -78.197200; 55.916500;,
-43.247200; -43.634600; -33.988800;,
0.007700; -84.077600; 13.618000;,
-40.100000; -78.197200; 55.916500;,
0.007700; -84.077600; 13.618000;,
-0.027500; -82.501200; 98.705800;,
-0.027500; -82.501200; 98.705800;,
-80.945400; -40.904400; 95.342400;,
-40.100000; -78.197200; 55.916500;,
0.007700; -84.077600; 13.618000;,
69.484800; -69.291600; 21.626400;,
56.333300; -56.298400; 84.155400;,
56.333300; -56.298400; 84.155400;,
-0.027500; -82.501200; 98.705800;,
0.007700; -84.077600; 13.618000;,
-0.027500; -82.501200; 98.705800;,
56.333300; -56.298400; 84.155400;,
42.584500; -42.599700; 142.365800;,
88.496300; 0.151500; 12.370400;,
69.484800; -69.291600; 21.626400;,
36.025700; -35.951600; -16.101700;,
36.025700; -35.951600; -16.101700;,
63.654800; 32.007700; -7.773900;,
88.496300; 0.151500; 12.370400;,
69.484800; -69.291600; 21.626400;,
88.496300; 0.151500; 12.370400;,
95.905200; -0.093000; 55.797800;,
88.496300; 0.151500; 12.370400;,
63.654800; 32.007700; -7.773900;,
94.781300; 46.478000; 55.820400;,
94.781300; 46.478000; 55.820400;,
95.905200; -0.093000; 55.797800;,
88.496300; 0.151500; 12.370400;,
69.484800; -69.291600; 21.626400;,
95.905200; -0.093000; 55.797800;,
56.333300; -56.298400; 84.155400;,
42.584500; -42.599700; 142.365800;,
56.333300; -56.298400; 84.155400;,
95.905200; -0.093000; 55.797800;,
95.905200; -0.093000; 55.797800;,
94.781300; 46.478000; 55.820400;,
42.584500; -42.599700; 142.365800;,
34.587400; 69.078200; 125.256100;,
42.584500; -42.599700; 142.365800;,
94.781300; 46.478000; 55.820400;,
63.654800; 32.007700; -7.773900;,
-41.390400; 41.060200; -27.017000;,
42.518800; 88.039100; 12.918800;,
42.518800; 88.039100; 12.918800;,
94.781300; 46.478000; 55.820400;,
63.654800; 32.007700; -7.773900;,
94.781300; 46.478000; 55.820400;,
42.518800; 88.039100; 12.918800;,
39.893500; 79.146200; 95.734200;,
0.085000; 98.270500; 56.135500;,
39.893500; 79.146200; 95.734200;,
42.518800; 88.039100; 12.918800;,
42.518800; 88.039100; 12.918800;,
-41.390400; 41.060200; -27.017000;,
-67.575800; 67.500000; 56.234100;,
-67.575800; 67.500000; 56.234100;,
0.085000; 98.270500; 56.135500;,
42.518800; 88.039100; 12.918800;,
39.893500; 79.146200; 95.734200;,
34.587400; 69.078200; 125.256100;,
94.781300; 46.478000; 55.820400;,
39.893500; 79.146200; 95.734200;,
0.085000; 98.270500; 56.135500;,
-41.569900; 85.015600; 97.796500;,
-67.575800; 67.500000; 56.234100;,
-41.569900; 85.015600; 97.796500;,
0.085000; 98.270500; 56.135500;,
39.893500; 79.146200; 95.734200;,
-41.569900; 85.015600; 97.796500;,
0.741600; 63.171600; 119.733100;,
0.741600; 63.171600; 119.733100;,
34.587400; 69.078200; 125.256100;,
39.893500; 79.146200; 95.734200;,
-72.737900; 37.495500; 129.261700;,
0.741600; 63.171600; 119.733100;,
-41.569900; 85.015600; 97.796500;,
-41.569900; 85.015600; 97.796500;,
-67.575800; 67.500000; 56.234100;,
-72.737900; 37.495500; 129.261700;,
-41.390400; 41.060200; -27.017000;,
-43.247200; -43.634600; -33.988800;,
-95.009100; -0.266800; 9.529300;,
-41.390400; 41.060200; -27.017000;,
-95.009100; -0.266800; 9.529300;,
-85.942300; 42.785200; 56.173100;,
-85.942300; 42.785200; 56.173100;,
-67.575800; 67.500000; 56.234100;,
-41.390400; 41.060200; -27.017000;,
-94.017100; -46.133700; 55.755300;,
-85.942300; 42.785200; 56.173100;,
-95.009100; -0.266800; 9.529300;,
-95.009100; -0.266800; 9.529300;,
-43.247200; -43.634600; -33.988800;,
-94.017100; -46.133700; 55.755300;,
-94.017100; -46.133700; 55.755300;,
-43.247200; -43.634600; -33.988800;,
-40.100000; -78.197200; 55.916500;,
-94.017100; -46.133700; 55.755300;,
-40.100000; -78.197200; 55.916500;,
-80.945400; -40.904400; 95.342400;,
-67.575800; 67.500000; 56.234100;,
-85.942300; 42.785200; 56.173100;,
-72.737900; 37.495500; 129.261700;,
-85.942300; 42.785200; 56.173100;,
-94.017100; -46.133700; 55.755300;,
-72.737900; 37.495500; 129.261700;,
-80.945400; -40.904400; 95.342400;,
-72.737900; 37.495500; 129.261700;,
-94.017100; -46.133700; 55.755300;;
50;
3; 0, 2, 1;,
3; 3, 5, 4;,
3; 6, 8, 7;,
3; 9, 11, 10;,
3; 12, 14, 13;,
3; 15, 17, 16;,
3; 18, 20, 19;,
3; 21, 23, 22;,
3; 24, 26, 25;,
3; 27, 29, 28;,
3; 30, 32, 31;,
3; 33, 35, 34;,
3; 36, 38, 37;,
3; 39, 41, 40;,
3; 42, 44, 43;,
3; 45, 47, 46;,
3; 48, 50, 49;,
3; 51, 53, 52;,
3; 54, 56, 55;,
3; 57, 59, 58;,
3; 60, 62, 61;,
3; 63, 65, 64;,
3; 66, 68, 67;,
3; 69, 71, 70;,
3; 72, 74, 73;,
3; 75, 77, 76;,
3; 78, 80, 79;,
3; 81, 83, 82;,
3; 84, 86, 85;,
3; 87, 89, 88;,
3; 90, 92, 91;,
3; 93, 95, 94;,
3; 96, 98, 97;,
3; 99, 101, 100;,
3; 102, 104, 103;,
3; 105, 107, 106;,
3; 108, 110, 109;,
3; 111, 113, 112;,
3; 114, 116, 115;,
3; 117, 119, 118;,
3; 120, 122, 121;,
3; 123, 125, 124;,
3; 126, 128, 127;,
3; 129, 131, 130;,
3; 132, 134, 133;,
3; 135, 137, 136;,
3; 138, 140, 139;,
3; 141, 143, 142;,
3; 144, 146, 145;,
3; 147, 149, 148;;
  MeshMaterialList {
    2;
    50;
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1;;
  Material Stone_F_1 {
    0.600000; 0.600000; 0.600000;1.0;;
    0.500000;
    0.900000; 0.900000; 0.900000;;
    0.0; 0.0; 0.0;;
  }  //End of Material
  Material Mat1 {
    1.0; 1.0; 1.0; 1.0;;
    1.0;
    1.0; 1.0; 1.0;;
    0.0; 0.0; 0.0;;
  TextureFilename {    "S1_LOD3D.jpg";  }
  }  // End of Material
    }  //End of MeshMaterialList
  MeshNormals {
150;
    0.403150; -0.370586; -0.836695;,
    -0.365337; -0.520798; -0.771538;,
    0.189367; 0.024415; -0.981597;,
    0.403150; -0.370586; -0.836695;,
    0.189367; 0.024415; -0.981597;,
    0.545885; 0.269906; -0.793176;,
    0.189367; 0.024415; -0.981597;,
    -0.365337; -0.520798; -0.771538;,
    -0.370983; 0.511124; -0.775292;,
    0.189367; 0.024415; -0.981597;,
    -0.370983; 0.511124; -0.775292;,
    0.545885; 0.269906; -0.793176;,
    -0.188971; -0.062960; 0.979949;,
    -0.706320; 0.340983; 0.620319;,
    -0.572222; -0.567461; 0.592029;,
    -0.572222; -0.567461; 0.592029;,
    -0.069094; -0.887722; 0.455123;,
    -0.188971; -0.062960; 0.979949;,
    0.593738; -0.296762; 0.747887;,
    -0.188971; -0.062960; 0.979949;,
    -0.069094; -0.887722; 0.455123;,
    -0.706320; 0.340983; 0.620319;,
    -0.188971; -0.062960; 0.979949;,
    -0.100192; 0.652669; 0.750969;,
    -0.188971; -0.062960; 0.979949;,
    0.593738; -0.296762; 0.747887;,
    0.308847; 0.566759; 0.763787;,
    0.308847; 0.566759; 0.763787;,
    -0.100192; 0.652669; 0.750969;,
    -0.188971; -0.062960; 0.979949;,
    -0.365337; -0.520798; -0.771538;,
    0.403150; -0.370586; -0.836695;,
    0.091525; -0.951506; -0.293588;,
    0.700491; -0.650838; -0.292673;,
    0.091525; -0.951506; -0.293588;,
    0.403150; -0.370586; -0.836695;,
    -0.419843; -0.907559; 0.003113;,
    -0.365337; -0.520798; -0.771538;,
    0.091525; -0.951506; -0.293588;,
    -0.419843; -0.907559; 0.003113;,
    0.091525; -0.951506; -0.293588;,
    -0.069094; -0.887722; 0.455123;,
    -0.069094; -0.887722; 0.455123;,
    -0.572222; -0.567461; 0.592029;,
    -0.419843; -0.907559; 0.003113;,
    0.091525; -0.951506; -0.293588;,
    0.700491; -0.650838; -0.292673;,
    0.590686; -0.769402; 0.243049;,
    0.590686; -0.769402; 0.243049;,
    -0.069094; -0.887722; 0.455123;,
    0.091525; -0.951506; -0.293588;,
    -0.069094; -0.887722; 0.455123;,
    0.590686; -0.769402; 0.243049;,
    0.593738; -0.296762; 0.747887;,
    0.847804; -0.065676; -0.526200;,
    0.700491; -0.650838; -0.292673;,
    0.403150; -0.370586; -0.836695;,
    0.403150; -0.370586; -0.836695;,
    0.545885; 0.269906; -0.793176;,
    0.847804; -0.065676; -0.526200;,
    0.700491; -0.650838; -0.292673;,
    0.847804; -0.065676; -0.526200;,
    0.955687; -0.242927; 0.166143;,
    0.847804; -0.065676; -0.526200;,
    0.545885; 0.269906; -0.793176;,
    0.905332; 0.416669; 0.082034;,
    0.905332; 0.416669; 0.082034;,
    0.955687; -0.242927; 0.166143;,
    0.847804; -0.065676; -0.526200;,
    0.700491; -0.650838; -0.292673;,
    0.955687; -0.242927; 0.166143;,
    0.590686; -0.769402; 0.243049;,
    0.593738; -0.296762; 0.747887;,
    0.590686; -0.769402; 0.243049;,
    0.955687; -0.242927; 0.166143;,
    0.955687; -0.242927; 0.166143;,
    0.905332; 0.416669; 0.082034;,
    0.593738; -0.296762; 0.747887;,
    0.308847; 0.566759; 0.763787;,
    0.593738; -0.296762; 0.747887;,
    0.905332; 0.416669; 0.082034;,
    0.545885; 0.269906; -0.793176;,
    -0.370983; 0.511124; -0.775292;,
    0.244148; 0.873714; -0.420667;,
    0.244148; 0.873714; -0.420667;,
    0.905332; 0.416669; 0.082034;,
    0.545885; 0.269906; -0.793176;,
    0.905332; 0.416669; 0.082034;,
    0.244148; 0.873714; -0.420667;,
    0.267220; 0.905209; 0.330363;,
    -0.097964; 0.994018; -0.047884;,
    0.267220; 0.905209; 0.330363;,
    0.244148; 0.873714; -0.420667;,
    0.244148; 0.873714; -0.420667;,
    -0.370983; 0.511124; -0.775292;,
    -0.602496; 0.775750; -0.187475;,
    -0.602496; 0.775750; -0.187475;,
    -0.097964; 0.994018; -0.047884;,
    0.244148; 0.873714; -0.420667;,
    0.267220; 0.905209; 0.330363;,
    0.308847; 0.566759; 0.763787;,
    0.905332; 0.416669; 0.082034;,
    0.267220; 0.905209; 0.330363;,
    -0.097964; 0.994018; -0.047884;,
    -0.253914; 0.868129; 0.426435;,
    -0.602496; 0.775750; -0.187475;,
    -0.253914; 0.868129; 0.426435;,
    -0.097964; 0.994018; -0.047884;,
    0.267220; 0.905209; 0.330363;,
    -0.253914; 0.868129; 0.426435;,
    -0.100192; 0.652669; 0.750969;,
    -0.100192; 0.652669; 0.750969;,
    0.308847; 0.566759; 0.763787;,
    0.267220; 0.905209; 0.330363;,
    -0.706320; 0.340983; 0.620319;,
    -0.100192; 0.652669; 0.750969;,
    -0.253914; 0.868129; 0.426435;,
    -0.253914; 0.868129; 0.426435;,
    -0.602496; 0.775750; -0.187475;,
    -0.706320; 0.340983; 0.620319;,
    -0.370983; 0.511124; -0.775292;,
    -0.365337; -0.520798; -0.771538;,
    -0.892697; 0.081484; -0.443190;,
    -0.370983; 0.511124; -0.775292;,
    -0.892697; 0.081484; -0.443190;,
    -0.910123; 0.408399; -0.069369;,
    -0.910123; 0.408399; -0.069369;,
    -0.602496; 0.775750; -0.187475;,
    -0.370983; 0.511124; -0.775292;,
    -0.920438; -0.389843; 0.027406;,
    -0.910123; 0.408399; -0.069369;,
    -0.892697; 0.081484; -0.443190;,
    -0.892697; 0.081484; -0.443190;,
    -0.365337; -0.520798; -0.771538;,
    -0.920438; -0.389843; 0.027406;,
    -0.920438; -0.389843; 0.027406;,
    -0.365337; -0.520798; -0.771538;,
    -0.419843; -0.907559; 0.003113;,
    -0.920438; -0.389843; 0.027406;,
    -0.419843; -0.907559; 0.003113;,
    -0.572222; -0.567461; 0.592029;,
    -0.602496; 0.775750; -0.187475;,
    -0.910123; 0.408399; -0.069369;,
    -0.706320; 0.340983; 0.620319;,
    -0.910123; 0.408399; -0.069369;,
    -0.920438; -0.389843; 0.027406;,
    -0.706320; 0.340983; 0.620319;,
    -0.572222; -0.567461; 0.592029;,
    -0.706320; 0.340983; 0.620319;,
    -0.920438; -0.389843; 0.027406;;
50;
3; 0, 2, 1;,
3; 3, 5, 4;,
3; 6, 8, 7;,
3; 9, 11, 10;,
3; 12, 14, 13;,
3; 15, 17, 16;,
3; 18, 20, 19;,
3; 21, 23, 22;,
3; 24, 26, 25;,
3; 27, 29, 28;,
3; 30, 32, 31;,
3; 33, 35, 34;,
3; 36, 38, 37;,
3; 39, 41, 40;,
3; 42, 44, 43;,
3; 45, 47, 46;,
3; 48, 50, 49;,
3; 51, 53, 52;,
3; 54, 56, 55;,
3; 57, 59, 58;,
3; 60, 62, 61;,
3; 63, 65, 64;,
3; 66, 68, 67;,
3; 69, 71, 70;,
3; 72, 74, 73;,
3; 75, 77, 76;,
3; 78, 80, 79;,
3; 81, 83, 82;,
3; 84, 86, 85;,
3; 87, 89, 88;,
3; 90, 92, 91;,
3; 93, 95, 94;,
3; 96, 98, 97;,
3; 99, 101, 100;,
3; 102, 104, 103;,
3; 105, 107, 106;,
3; 108, 110, 109;,
3; 111, 113, 112;,
3; 114, 116, 115;,
3; 117, 119, 118;,
3; 120, 122, 121;,
3; 123, 125, 124;,
3; 126, 128, 127;,
3; 129, 131, 130;,
3; 132, 134, 133;,
3; 135, 137, 136;,
3; 138, 140, 139;,
3; 141, 143, 142;,
3; 144, 146, 145;,
3; 147, 149, 148;;
}  //End of MeshNormals
MeshTextureCoords {
150;
0.497412;-0.376564;,
0.265672;-0.372605;,
0.264464;-0.282858;,
0.497412;-0.376564;,
0.264464;-0.282858;,
0.496102;-0.198480;,
0.264464;-0.282858;,
0.281054;-0.163230;,
0.389919;-0.119736;,
0.264464;-0.282858;,
0.389919;-0.119736;,
0.496102;-0.198480;,
0.387904;-0.730075;,
0.265714;-0.775752;,
0.271700;-0.597719;,
0.271700;-0.597719;,
0.400645;-0.597196;,
0.387904;-0.730075;,
0.507364;-0.777073;,
0.387904;-0.730075;,
0.400645;-0.597196;,
0.265714;-0.775752;,
0.387904;-0.730075;,
0.330957;-0.853769;,
0.387904;-0.730075;,
0.507364;-0.777073;,
0.445792;-0.854059;,
0.445792;-0.854059;,
0.330957;-0.853769;,
0.387904;-0.730075;,
0.265672;-0.372605;,
0.497412;-0.376564;,
0.392851;-0.489131;,
0.504148;-0.486898;,
0.392851;-0.489131;,
0.497412;-0.376564;,
0.264710;-0.484888;,
0.265672;-0.372605;,
0.392851;-0.489131;,
0.264710;-0.484888;,
0.392851;-0.489131;,
0.400645;-0.597196;,
0.400645;-0.597196;,
0.271700;-0.597719;,
0.264710;-0.484888;,
0.392851;-0.489131;,
0.504148;-0.486898;,
0.496550;-0.602071;,
0.496550;-0.602071;,
0.400645;-0.597196;,
0.392851;-0.489131;,
0.400645;-0.597196;,
0.496550;-0.602071;,
0.507364;-0.777073;,
0.670949;-0.360121;,
0.504148;-0.486898;,
0.497412;-0.376564;,
0.497412;-0.376564;,
0.614049;-0.354306;,
0.670949;-0.360121;,
0.504148;-0.486898;,
0.670949;-0.360121;,
0.620510;-0.486870;,
0.670949;-0.360121;,
0.728703;-0.383617;,
0.708036;-0.470112;,
0.708036;-0.470112;,
0.620510;-0.486870;,
0.670949;-0.360121;,
0.504148;-0.486898;,
0.620510;-0.486870;,
0.496550;-0.602071;,
0.676207;-0.607213;,
0.496550;-0.602071;,
0.620510;-0.486870;,
0.620510;-0.486870;,
0.708036;-0.470112;,
0.676207;-0.607213;,
0.723387;-0.587147;,
0.676207;-0.607213;,
0.708036;-0.470112;,
0.728703;-0.383617;,
0.908819;-0.363444;,
0.841825;-0.405966;,
0.841825;-0.405966;,
0.708036;-0.470112;,
0.728703;-0.383617;,
0.708036;-0.470112;,
0.841825;-0.405966;,
0.799077;-0.541402;,
0.938399;-0.487095;,
0.799077;-0.541402;,
0.841825;-0.405966;,
0.841825;-0.405966;,
0.908819;-0.363444;,
0.991767;-0.490430;,
0.991767;-0.490430;,
0.938399;-0.487095;,
0.841825;-0.405966;,
0.799077;-0.541402;,
0.723387;-0.587147;,
0.708036;-0.470112;,
0.799077;-0.541402;,
0.938399;-0.487095;,
0.930597;-0.558593;,
0.991767;-0.490430;,
0.930597;-0.558593;,
0.938399;-0.487095;,
0.799077;-0.541402;,
0.930597;-0.558593;,
0.840844;-0.611792;,
0.840844;-0.611792;,
0.723387;-0.587147;,
0.799077;-0.541402;,
0.954493;-0.594804;,
0.840844;-0.611792;,
0.930597;-0.558593;,
0.930597;-0.558593;,
0.991767;-0.490430;,
0.954493;-0.594804;,
0.068511;-0.378276;,
0.265672;-0.372605;,
0.139699;-0.414821;,
0.068511;-0.378276;,
0.139699;-0.414821;,
0.080922;-0.487007;,
0.080922;-0.487007;,
0.010928;-0.486990;,
0.068511;-0.378276;,
0.154750;-0.488818;,
0.080922;-0.487007;,
0.139699;-0.414821;,
0.139699;-0.414821;,
0.265672;-0.372605;,
0.154750;-0.488818;,
0.154750;-0.488818;,
0.265672;-0.372605;,
0.264710;-0.484888;,
0.154750;-0.488818;,
0.264710;-0.484888;,
0.271700;-0.597719;,
0.010928;-0.486990;,
0.080922;-0.487007;,
0.055971;-0.588104;,
0.080922;-0.487007;,
0.154750;-0.488818;,
0.055971;-0.588104;,
0.271700;-0.597719;,
0.055971;-0.588104;,
0.154750;-0.488818;;
}  //End of MeshTextureCoords
 }
}
}
