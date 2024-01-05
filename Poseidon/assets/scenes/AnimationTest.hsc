Scene: Scene Name
Environment:
  AssetPath: assets\env\birchwood_4k.hdr
  Light:
    Direction: [-0.788999975, 0.777999997, -0.782999992]
    Radiance: [1, 0.999989986, 0.999989986]
    Multiplier: 0.651000023
Entities:
  - Entity: 6605693014656896610
    TagComponent:
      Tag: Sky Light
    TransformComponent:
      Position: [0, 0, 0]
      Rotation: [1, 0, 0, 0]
      Scale: [1, 1, 1]
    SkyLightComponent:
      EnvironmentAssetPath: assets\env\birchwood_4k.hdr
      Intensity: 1
      Angle: 0
  - Entity: 3370882484222092056
    TagComponent:
      Tag: Directional Light
    TransformComponent:
      Position: [0, 0, 0]
      Rotation: [0.68972528, 0.70944953, 0.144718781, -0.00410703989]
      Scale: [1.00000012, 0.999994099, 0.999999523]
    DirectionalLightComponent:
      Radiance: [1, 1, 1]
      CastShadows: true
      SoftShadows: true
      LightSize: 0.5
  - Entity: 11293686930003950360
    TagComponent:
      Tag: Scene
    TransformComponent:
      Position: [-2.90346504e-23, -0.274215937, -4.87120601e-16]
      Rotation: [1, 8.8820616e-16, 2.98023224e-08, -2.64706063e-23]
      Scale: [21.1364994, 21.1364994, 21.1364994]
    MeshComponent:
      AssetPath: assets\meshes\CubeScene.fbx
  - Entity: 7475399290764333888
    TagComponent:
      Tag: Sphere
    TransformComponent:
      Position: [3.20819902, 4.03841782, -7.22279453]
      Rotation: [1, 0, 0, 0]
      Scale: [3.71339679, 3.71339679, 3.71339679]
    MeshComponent:
      AssetPath: assets\meshes\Sphere1m.fbx
  - Entity: 10259309054909760418
    TagComponent:
      Tag: Gun
    TransformComponent:
      Position: [3.64099932, 3.55597281, 5.70084906]
      Rotation: [0.953514934, 0.0584657155, -0.295065552, 0.0180922709]
      Scale: [25.793951, 25.7939529, 25.7939472]
    MeshComponent:
      AssetPath: assets\models\m1911\m1911.fbx
  - Entity: 8985316210871459427
    TagComponent:
      Tag: Stormtrooper
    TransformComponent:
      Position: [-10.306489, 0.14903906, -7.11563587]
      Rotation: [0.99873203, 0, -0.0503417216, 0]
      Scale: [2.06998873, 2.06998801, 2.06998873]
    MeshComponent:
      AssetPath: assets\meshes\stormtrooper\silly_dancing.fbx
  - Entity: 11848937967922634750
    TagComponent:
      Tag: Pilot
    TransformComponent:
      Position: [-10.306489, 0.14903906, -7.11563587]
      Rotation: [0.99873203, 0, -0.0503417216, 0]
      Scale: [-2.59314743e-36, 7.41286888e-43, 2.06998873]
    MeshComponent:
      AssetPath: assets\meshes\pilot\Pilot_LP_Animated.fbx