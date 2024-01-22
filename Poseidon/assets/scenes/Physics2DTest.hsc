Scene: Scene Name
Environment:
  AssetHandle: 5052087455964462420
  Light:
    Direction: [0, 0, 0]
    Radiance: [0, 0, 0]
    Multiplier: 1
Entities:
  - Entity: 3459685244807816640
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
      EnvironmentMap: 5052087455964462420
      Intensity: 1
      Angle: 0
  - Entity: 12985049603524075809
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
  - Entity: 3948844418381294888
    Parent: 0
    Children:
      []
    TagComponent:
      Tag: Box
    TransformComponent:
      Position: [-1.48028564, 49.5945244, -2.38418579e-07]
      Rotation: [0, 0, 0]
      Scale: [1.99999976, 1.99999976, 2]
    MeshComponent:
      AssetID: 9699802212392322834
    RigidBody2DComponent:
      BodyType: 1
      FixedRotation: false
    BoxCollider2DComponent:
      Offset: [0, 0]
      Size: [1, 1]
      Density: 1
      Friction: 1
  - Entity: 5178862374589434728
    Parent: 0
    Children:
      []
    TagComponent:
      Tag: Camera
    TransformComponent:
      Position: [0, 25, 79.75]
      Rotation: [0, 0, 0]
      Scale: [1, 0.999999821, 0.999999821]
    ScriptComponent:
      ModuleName: Example.BasicController
      StoredFields:
        - Name: Speed
          Type: 1
          Data: 12
        - Name: DistanceFromPlayer
          Type: 1
          Data: 0
    CameraComponent:
      Camera:
        ProjectionType: 0
        PerspectiveFOV: 45
        PerspectiveNear: 0.100000001
        PerspectiveFar: 1000
        OrthographicSize: 10
        OrthographicNear: -1
        OrthographicFar: 1
      Primary: true
  - Entity: 1289165777996378215
    Parent: 0
    Children:
      []
    TagComponent:
      Tag: Cube
    TransformComponent:
      Position: [0, 0, 0]
      Rotation: [0, 0, 0]
      Scale: [50, 1, 50]
    ScriptComponent:
      ModuleName: Example.Sink
      StoredFields:
        - Name: SinkSpeed
          Type: 1
          Data: 0
    MeshComponent:
      AssetID: 9699802212392322834
    RigidBody2DComponent:
      BodyType: 0
      FixedRotation: false
    BoxCollider2DComponent:
      Offset: [0, 0]
      Size: [25, 0.5]
      Density: 1
      Friction: 1
  - Entity: 14057422478420564497
    Parent: 0
    Children:
      []
    TagComponent:
      Tag: Player
    TransformComponent:
      Position: [0, 22.774044, 0]
      Rotation: [0, 0, 0]
      Scale: [6.00000048, 6.00000048, 4.48000002]
    ScriptComponent:
      ModuleName: Example.PlayerCube
      StoredFields:
        - Name: HorizontalForce
          Type: 1
          Data: 10
        - Name: MaxSpeed
          Type: 5
          Data: [0, 0]
        - Name: JumpForce
          Type: 1
          Data: 0
        - Name: VerticalForce
          Type: 1
          Data: 10
    MeshComponent:
      AssetID: 2853222666109707451
    RigidBody2DComponent:
      BodyType: 1
      FixedRotation: false
    CircleCollider2DComponent:
      Offset: [0, 0]
      Radius: 3
      Density: 1
      Friction: 1
  - Entity: 935615878363259513
    Parent: 0
    Children:
      []
    TagComponent:
      Tag: Box
    TransformComponent:
      Position: [6.88031197, 31.942337, 0]
      Rotation: [0, 0, 0]
      Scale: [4.47999954, 4.47999954, 4.48000002]
    MeshComponent:
      AssetID: 9699802212392322834
    RigidBody2DComponent:
      BodyType: 1
      FixedRotation: false
    BoxCollider2DComponent:
      Offset: [0, 0]
      Size: [2.24000001, 2.24000001]
      Density: 1
      Friction: 1
  - Entity: 1352995477042327524
    Parent: 0
    Children:
      []
    TagComponent:
      Tag: Box
    TransformComponent:
      Position: [-8.32969856, 30.4078159, 0]
      Rotation: [0, 0, 0]
      Scale: [14.000001, 4.47999334, 4.48000002]
    MeshComponent:
      AssetID: 9699802212392322834
    RigidBody2DComponent:
      BodyType: 1
      FixedRotation: false
    BoxCollider2DComponent:
      Offset: [0, 0]
      Size: [7, 2.24000001]
      Density: 1
      Friction: 1
  - Entity: 8080964283681139153
    Parent: 0
    Children:
      []
    TagComponent:
      Tag: Box
    TransformComponent:
      Position: [-0.739211679, 37.7653275, 0]
      Rotation: [0, 0, 0]
      Scale: [5, 2, 2]
    MeshComponent:
      AssetID: 9699802212392322834
    RigidBody2DComponent:
      BodyType: 1
      FixedRotation: false
    BoxCollider2DComponent:
      Offset: [0, 0]
      Size: [2.5, 1]
      Density: 1
      Friction: 1
  - Entity: 2157107598622182863
    Parent: 0
    Children:
      []
    TagComponent:
      Tag: Box
    TransformComponent:
      Position: [-7.60411549, 44.1442184, 0]
      Rotation: [0, 0, 0]
      Scale: [4.47999287, 4.47999287, 4.48000002]
    MeshComponent:
      AssetID: 9699802212392322834
    RigidBody2DComponent:
      BodyType: 1
      FixedRotation: false
    BoxCollider2DComponent:
      Offset: [0, 0]
      Size: [2.24000001, 2.24000001]
      Density: 1
      Friction: 1
  - Entity: 15223077898852293773
    Parent: 0
    Children:
      []
    TagComponent:
      Tag: Box
    TransformComponent:
      Position: [5.37119865, 43.8762894, 0]
      Rotation: [0, 0, 0]
      Scale: [4.47999668, 4.47999668, 4.48000002]
    MeshComponent:
      AssetID: 9699802212392322834
    RigidBody2DComponent:
      BodyType: 1
      FixedRotation: false
    BoxCollider2DComponent:
      Offset: [0, 0]
      Size: [2.24000001, 2.24000001]
      Density: 1
      Friction: 1
  - Entity: 15861629587505754
    Parent: 0
    Children:
      []
    TagComponent:
      Tag: Box
    TransformComponent:
      Position: [-18.2095661, 39.2518234, 0]
      Rotation: [0, 0, 0]
      Scale: [4.47999525, 4.47999525, 4.48000002]
    MeshComponent:
      AssetID: 9699802212392322834
    RigidBody2DComponent:
      BodyType: 1
      FixedRotation: false
    BoxCollider2DComponent:
      Offset: [0, 0]
      Size: [2.24000001, 2.24000001]
      Density: 1
      Friction: 1
PhysicsLayers:
  []