Scene: Scene Name
Environment:
  AssetHandle: 2514227705835677036
  Light:
    Direction: [0, 0, 0]
    Radiance: [0, 0, 0]
    Multiplier: 1
Entities:
  - Entity: 2669824871856367699
    Parent: 0
    Children:
      []
    TagComponent:
      Tag: Directional Light
    TransformComponent:
      Position: [0, 0, 0]
      Rotation: [1.39626336, 0.17453292, 0]
      Scale: [1, 1, 1]
    DirectionalLightComponent:
      Radiance: [1, 1, 1]
      CastShadows: true
      SoftShadows: true
      LightSize: 0.5
  - Entity: 12533361872387644690
    Parent: 0
    Children:
      []
    TagComponent:
      Tag: Sky Light
    TransformComponent:
      Position: [0, 0, 0]
      Rotation: [0, 0, 0]
      Scale: [1, 1, 1]
    SkyLightComponent:
      EnvironmentMap: 2514227705835677036
      Intensity: 1
      Angle: 0
  - Entity: 12057074290494475737
    Parent: 0
    Children:
      - Handle: 6378979277065937606
    TagComponent:
      Tag: Cube
    TransformComponent:
      Position: [3.07457423, 0, 0]
      Rotation: [0, 0, 0]
      Scale: [1, 1, 1]
    MeshComponent:
      AssetID: 16316222733560087453
  - Entity: 6378979277065937606
    Parent: 12057074290494475737
    Children:
      []
    TagComponent:
      Tag: Sphere
    TransformComponent:
      Position: [-3.07022738, 0, 0]
      Rotation: [0, 0, 0]
      Scale: [1, 1, 1]
    MeshComponent:
      AssetID: 10072064586026924578
PhysicsLayers:
  []