'use strict';

class ShaderLib {
  constructor() {
  }

  phongVertex() {
    return `
      attribute vec3 vertex;
      attribute vec3 normal;
      attribute vec3 color;
      uniform mat4 mvMat;
      uniform mat4 mvpMat;
      uniform mat3 nMat;
      varying vec3 vVertex;
      varying vec3 vNormal;
      varying vec3 vColor;
      void main()
      {
        vec4 vertex4 = vec4(vertex, 1.0);
        vNormal = nMat * normal;
        vColor = color;
        vVertex = vec3(mvMat * vertex4);
        gl_Position = mvpMat * vertex4;
      }
    `;
  }

  phongFragment() {
    return `
      precision mediump float;
      uniform vec3 centerPicking;
      uniform float radiusSquared;
      uniform vec2 lineOrigin;
      uniform vec2 lineNormal;
      varying vec3 vVertex;
      varying vec3 vNormal;
      varying vec3 vColor;
      const vec3 colorBackface = vec3(0.81, 0.71, 0.23);
      const vec4 colorCutPlane = vec4(0.81, 0.31, 0.23, 1.0);
      const vec3 vecLight = vec3(0.06189844605901729, 0.12379689211803457, 0.9903751369442766);
      const float shininess = 100.0;
      void main()
      {
        vec3 normal;
        vec3 fragColor;
        if(gl_FrontFacing)
        {
          normal = vNormal;
          fragColor = vColor;
        }
        else
        {
          normal = -vNormal;
          fragColor = colorBackface;
        }
        float dotLN = dot(normal, vecLight);
        vec3 vecR = normalize(2.0 * dotLN * normal - vecLight);
        float dotRVpow = pow(dot(vecR, vecLight), shininess);
        vec3 ambiant = fragColor * 0.5;
        vec3 diffuse = fragColor * 0.5 * max(0.0, dotLN);
        vec3 specular = fragColor * 0.8 * max(0.0, dotRVpow);
        fragColor = ambiant + diffuse + specular;
        vec3 vecDistance = vVertex - centerPicking;
        float dotSquared = dot(vecDistance, vecDistance);
        if(dotSquared < radiusSquared * 1.06 && dotSquared > radiusSquared * 0.94)
          fragColor *= 0.5;
        else if(dotSquared < radiusSquared)
          fragColor *= 1.1;
        if(dot(lineNormal, vec2(gl_FragCoord) - lineOrigin) <= 0.0)
          gl_FragColor = vec4(fragColor, 1.0);
        else
          gl_FragColor = vec4(fragColor, 1.0) * colorCutPlane;
      }
    `;
  }

  transparencyVertex() {
    return `
    attribute vec3 vertex;
    attribute vec3 normal;
    attribute vec3 color;
    uniform mat4 mvMat;
    uniform mat4 mvpMat;
    uniform mat3 nMat;
    varying vec3 vVertex;
    varying vec3 vNormal;
    varying vec3 vColor;
    void main()
    {
      vec4 vertex4 = vec4(vertex, 1.0);
      vNormal = nMat * normal;
      vColor = color;
      vVertex = vec3(mvMat * vertex4);
      gl_Position = mvpMat * vertex4;
    }
    `;
  }

  transparencyFragment() {
    return `
    precision mediump float;
    uniform vec3 centerPicking;
    uniform float radiusSquared;
    uniform vec2 lineOrigin;
    uniform vec2 lineNormal;
    varying vec3 vVertex;
    varying vec3 vNormal;
    varying vec3 vColor;
    const vec3 vecLight = vec3(0.06189844605901729, 0.12379689211803457, 0.9903751369442766);
    const vec4 colorCutPlane = vec4(0.81, 0.31, 0.23, 1.0);
    const float shininess = 1000.0;
    void main ()
    {
      vec4 color = vec4(vColor, 0.05);
      vec4 specularColor = color * 0.5;
      specularColor.a = color.a * 3.0;
      float specular = max(dot(-vecLight, -reflect(vecLight, vNormal)), 0.0);
      vec4 fragColor = color + specularColor * (specular + pow(specular, shininess));
      vec3 vecDistance = vVertex-centerPicking;
      float dotSquared = dot(vecDistance,vecDistance);
      if(dotSquared < radiusSquared * 1.06 && dotSquared > radiusSquared * 0.94)
        fragColor *= 0.5;
      else if(dotSquared < radiusSquared)
        fragColor *= 1.1;
      if(dot(lineNormal, vec2(gl_FragCoord) - lineOrigin) <= 0.0)
        gl_FragColor = fragColor;
      else
        gl_FragColor = fragColor * colorCutPlane;
    }
    `;
  }

  wireframeVertex() {
    return `
    attribute vec3 vertex;
    attribute vec4 normal;
    uniform mat4 mvMat, mvpMat;
    uniform mat3 nMat;
    varying vec3 vVertex;
    varying vec3 vNormal;
    varying vec3 vBarycenter;
    void main()
    {
      vec4 vertex4 = vec4(vertex, 1.0);
      float bVal = normal[3];
      if(bVal > 1.5)
        vBarycenter = vec3(0,0,1);
      else if(bVal < 0.5)
        vBarycenter = vec3(0,1,0);
      else
        vBarycenter = vec3(1,0,0);
      vNormal = nMat * vec3(normal);
      vVertex = vec3(mvMat * vertex4);
      gl_Position = mvpMat * vertex4;
    }
    `;
  }

  wireframeFragment() {
    return `
    precision mediump float;
    uniform vec3 centerPicking;
    uniform float radiusSquared;
    uniform vec2 lineOrigin;
    uniform vec2 lineNormal;
    varying vec3 vVertex;
    varying vec3 vNormal;
    varying vec3 vBarycenter;
    const vec3 colorBackface = vec3(0.81, 0.71, 0.23);
    const vec4 colorCutPlane = vec4(0.81, 0.31, 0.23, 1.0);
    const vec3 vecLight = vec3(0.06189844605901729, 0.12379689211803457, 0.9903751369442766);
    const float shininess = 100.0;
    void main()
    {
      vec3 normal;
      vec3 fragColor;
      if(gl_FrontFacing)
      {
        normal = vNormal;
        fragColor = vec3(0.5, 0.5, 0.5);
      }
      else
      {
        normal = - vNormal;
        fragColor = colorBackface;
      }
      float dotLN = dot(normal, vecLight);
      vec3 vecR = normalize(2.0 * dotLN * normal - vecLight);
      float dotRVpow = pow(dot(vecR, vecLight), shininess);
      vec3 ambiant = fragColor * 0.5;
      vec3 diffuse = fragColor * 0.5 * max(0.0, dotLN);
      vec3 specular = fragColor * 0.8 * max(0.0, dotRVpow);
      fragColor = ambiant + diffuse + specular;
      vec3 vecDistance = vVertex - centerPicking;
      float dotSquared = dot(vecDistance, vecDistance);
      if(dotSquared < radiusSquared * 1.06 && dotSquared > radiusSquared * 0.94)
        fragColor *= 0.5;
      else if(dotSquared<radiusSquared)
        fragColor *= 1.1;
      if(any(lessThan(vBarycenter, vec3(0.05))))
        fragColor = mix(fragColor * 0.5, fragColor, 20.0 * min(min(vBarycenter.x, vBarycenter.y), vBarycenter.z));
      if(dot(lineNormal, vec2(gl_FragCoord) - lineOrigin) <= 0.0)
        gl_FragColor = vec4(fragColor, 1.0);
      else
        gl_FragColor = vec4(fragColor, 1.0) * colorCutPlane;
    }
    `;
  }

  normalVertex() {
    return `
      attribute vec3 vertex;
      attribute vec3 normal;
      uniform mat4 mvMat;
      uniform mat4 mvpMat;
      uniform mat3 nMat;
      varying vec3 vVertex;
      varying vec3 vNormal;
      void main()
      {
        vec4 vert4 = vec4(vertex, 1.0);
        vNormal = normal;
        vVertex = vec3(mvMat * vert4);
        gl_Position = mvpMat * vert4;
      }
    `;
  }

  normalFragment() {
    return  `
      precision mediump float;
      uniform vec3 centerPicking;
      uniform float radiusSquared;
      uniform vec2 lineOrigin;
      uniform vec2 lineNormal;
      varying vec3 vVertex;
      varying vec3 vNormal;
      const vec4 colorCutPlane = vec4(0.81, 0.31, 0.23, 1.0);
      void main()
      {
        vec3 fragColor = vNormal * 0.5 + 0.5;
        vec3 vecDistance = vVertex - centerPicking;
        float dotSquared = dot(vecDistance, vecDistance);
        if(dotSquared < radiusSquared * 1.06 && dotSquared > radiusSquared * 0.94)
          fragColor *= 0.5;
        else if(dotSquared < radiusSquared)
          fragColor *= 1.1;
        if(dot(lineNormal, vec2(gl_FragCoord) - lineOrigin) <= 0.0)
          gl_FragColor = vec4(fragColor, 1.0);
        else
          gl_FragColor = vec4(fragColor, 1.0) * colorCutPlane;
      }
    `;
  }

  reflectionVertex() {
    return  `
    attribute vec3 vertex;
    attribute vec3 normal;
    attribute vec3 color;
    uniform mat4 mvMat;
    uniform mat4 mvpMat;
    uniform mat3 nMat;
    varying vec3 vVertex;
    varying vec3 vNormal;
    varying vec3 vColor;
    void main()
    {
      vec4 vertex4 = vec4(vertex, 1.0);
      vNormal = nMat * normal;
      vVertex = vec3(mvMat * vertex4);
      vColor = color;
      vec3 nm_z = normalize(vVertex);
      vec3 nm_x = cross(nm_z, vec3(0.0, 1.0, 0.0));
      vec3 nm_y = cross(nm_x, nm_z);
      vNormal = vec3(dot(vNormal, nm_x), dot(vNormal, nm_y), dot(vNormal, nm_z));
      gl_Position = mvpMat * vertex4;
    }
    `;
  }

  reflectionFragment() {
    return `
    precision mediump float;
    uniform sampler2D refTex;
    uniform vec3 centerPicking;
    uniform vec2 lineOrigin;
    uniform vec2 lineNormal;
    uniform float radiusSquared;
    varying vec3 vVertex;
    varying vec3 vNormal;
    varying vec3 vColor;
    const vec4 colorCutPlane = vec4(0.81, 0.31, 0.23, 1.0);
    const vec4 v4one = vec4(1.0);
    void main()
    {
      vec2 texCoord = vec2(0.5 * vNormal.x + 0.5, - 0.5 * vNormal.y - 0.5);
      vec4 vertColor = vec4(vColor, 1.0);
      vec4 fragColor = texture2D(refTex, texCoord) * vertColor;
      vec3 vecDistance = vVertex - centerPicking;
      float dotSquared = dot(vecDistance, vecDistance);
      if(dotSquared < radiusSquared * 1.06 && dotSquared > radiusSquared * 0.94)
        fragColor *= 0.5;
      else if(dotSquared < radiusSquared)
        fragColor *= 1.1;
      fragColor.a = 1.0;
      if(dot(lineNormal, vec2(gl_FragCoord) - lineOrigin) <= 0.0)
        gl_FragColor = fragColor;
      else
        gl_FragColor = fragColor * colorCutPlane;
    }
    `;
  }

  backgroundVertex() {
    return `
    attribute vec2 vertex;
    attribute vec2 texCoord;
    varying vec2 vTexCoord;
    void main()
    {
      vTexCoord = texCoord;
      gl_Position = vec4(vertex, 0.5, 1.0);
    }
    `;
  }

  backgroundFragment() {
    return `
    precision mediump float;
    uniform sampler2D backgroundTex;
    varying vec2 vTexCoord;
    void main()
    {
      gl_FragColor =  texture2D(backgroundTex, vTexCoord);
    }
    `;
  }

};
