var Export = {};

/** Export OBJ file */
Export.exportOBJ = function (mesh, mtl_name)
{
  var vAr = mesh.vertexArray_;
  var cAr = mesh.colorArray_;
  var iAr = mesh.indexArray_;
  var data = 's 0\n';

  if (mtl_name)
  {
    data += 'mtllib ' + mtl_name + '.mtl\n';
    data += 'usemtl ' + mtl_name + '\n';
  }
  var nbVertices = mesh.vertices_.length;
  var nbTriangles = mesh.triangles_.length;
  var scale = 1 / mesh.scale_;
  var i = 0,
    j = 0;
  for (i = 0; i < nbVertices; ++i)
  {
    j = i * 3;
    if(mtl_name)
      data += 'v ' + vAr[j] * scale + ' ' + vAr[j + 1] * scale + ' ' + vAr[j + 2] * scale + ' ' + cAr[j] + ' ' + cAr[j + 1 ] + ' ' + cAr[j + 2] + '\n';
    else
      data += 'v ' + vAr[j] * scale + ' ' + vAr[j + 1] * scale + ' ' + vAr[j + 2] * scale + '\n';
  }
  for (i = 0; i < nbTriangles; ++i)
  {
    j = i * 3;
    data += 'f ' + (1 + iAr[j]) + ' ' + (1 + iAr[j + 1]) + ' ' + (1 + iAr[j + 2]) + '\n';
  }
  return data;
};

/** Export STL file */
Export.exportSTL = function (mesh)
{
  return Export.exportAsciiSTL(mesh);
};

/** Export Ascii STL file */
Export.exportAsciiSTL = function (mesh)
{
  var vAr = mesh.vertexArray_;
  var iAr = mesh.indexArray_;
  var data = 'solid mesh\n';
  var triangles = mesh.triangles_;
  var nbTriangles = triangles.length;
  var scale = 1.0 / mesh.scale_;
  var i = 0,
    j = 0;
  for (i = 0; i < nbTriangles; ++i)
  {
    j = i * 3;
    var n = triangles[i].normal_;
    data += ' facet normal ' + n[0] + ' ' + n[1] + ' ' + n[2] + '\n';
    data += '  outer loop\n';
    var iv1 = iAr[j] * 3,
      iv2 = iAr[j + 1] * 3,
      iv3 = iAr[j + 2] * 3;
    data += '   vertex ' + vAr[iv1] * scale + ' ' + vAr[iv1 + 1] * scale + ' ' + vAr[iv1 + 2] * scale + '\n';
    data += '   vertex ' + vAr[iv2] * scale + ' ' + vAr[iv2 + 1] * scale + ' ' + vAr[iv2 + 2] * scale + '\n';
    data += '   vertex ' + vAr[iv3] * scale + ' ' + vAr[iv3 + 1] * scale + ' ' + vAr[iv3 + 2] * scale + '\n';
    data += '  endloop\n';
    data += ' endfacet\n';
  }
  data += 'endsolid mesh\n';
  return data;
};

/** Export PLY file */
Export.exportPLY = function (mesh)
{
  return Export.exportAsciiPLY(mesh);
};

/** Export Ascii PLY file */
Export.exportAsciiPLY = function (mesh)
{
  var vAr = mesh.vertexArray_;
  var cAr = mesh.colorArray_;
  var iAr = mesh.indexArray_;
  var data = 'ply\nformat ascii 1.0\ncomment created by SculptGL\n';
  var nbVertices = mesh.vertices_.length;
  var nbTriangles = mesh.triangles_.length;
  var scale = 1.0 / mesh.scale_;
  var i = 0,
    j = 0;
  data += 'element vertex ' + nbVertices + '\n';
  data += 'property float x\nproperty float y\nproperty float z\n';
  data += 'property uchar red\nproperty uchar green\nproperty uchar blue\n';
  data += 'element face ' + nbTriangles + '\n';
  data += 'property list uchar uint vertex_indices\nend_header\n';
  for (i = 0; i < nbVertices; ++i)
  {
    j = i * 3;
    data += vAr[j] * scale + ' ' +
      vAr[j + 1] * scale + ' ' +
      vAr[j + 2] * scale + ' ' +
      ((cAr[j] * 0xff) | 0) + ' ' +
      ((cAr[j + 1] * 0xff) | 0) + ' ' +
      ((cAr[j + 2] * 0xff) | 0) + '\n';
  }
  for (i = 0; i < nbTriangles; ++i)
  {
    j = i * 3;
    data += '3 ' + iAr[j] + ' ' + iAr[j + 1] + ' ' + iAr[j + 2] + '\n';
  }
  return data;
};

Export.exportSpecularMtl = function ()
{
    var data = 'newmtl specular\n';
    data += 'Ks 1.0 1.0 1.0\n';
    data += 'Ns 200.0\n';
    data += 'd 1.0\n'; // no transparency
    return data;
};

/** Export OBJ file to Sketchfab */
Export.exportSketchfab = function (mesh)
{
  // create a zip containing the .obj model
  var model = Export.exportOBJ(mesh, 'specular');
  var mtl = Export.exportSpecularMtl();
  var zip = new JSZip();
  zip.file('model.obj', model);
  zip.file('specular.mtl', mtl);
  var blob = zip.generate(
  {
    type: 'blob',
    compression: 'DEFLATE'
  });

  var options = {
    'fileModel': blob,
    'filenameModel': 'model.zip',
    'title': ''
  };

  Sketchfab.showUploader(options);
};
