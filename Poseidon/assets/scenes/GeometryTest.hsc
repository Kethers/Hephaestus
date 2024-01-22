Scene: Scene Name
Environment:
  AssetHandle: 5052087455964462420
  Light:
    Direction: [0, 0, 0]
    Radiance: [0, 0, 0]
    Multiplier: 1
Entities:
  - Entity: 17927773119720974910
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
  - Entity: 15965451688358928939
    Parent: 0
    Children:
      []
    TagComponent:
      Tag: Cube
    TransformComponent:
      Position: [-0.107480526, 0, 0]
      Rotation: [0, 0, 0]
      Scale: [10, 0.200000003, 10]
    MeshComponent:
      AssetID: 16316222733560087453
    BoxColliderComponent:
      Offset: [0, 0, 0]
      Size: [1, 1, 1]
      IsTrigger: false
      Material: 0
  - Entity: 13400502743876758863
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
  - Entity: 13484085775382976538
    Parent: 0
    Children:
      []
    TagComponent:
      Tag: Cube
    TransformComponent:
      Position: [-0.408517599, 0.863398671, -1.03821564]
      Rotation: [0, 0, 0]
      Scale: [1, 1, 1]
    MeshComponent:
      AssetID: 16316222733560087453
    RigidBodyComponent:
      BodyType: 1
      Mass: 1
      LinearDrag: 0
      AngularDrag: 0.0500000007
      DisableGravity: false
      IsKinematic: false
      Layer: 0
      Constraints:
        LockPositionX: false
        LockPositionY: false
        LockPositionZ: false
        LockRotationX: false
        LockRotationY: false
        LockRotationZ: false
    BoxColliderComponent:
      Offset: [0, 0, 0]
      Size: [1, 1, 1]
      IsTrigger: false
      Material: 0
  - Entity: 15990071018705454781
    Parent: 0
    Children:
      []
    TagComponent:
      Tag: Sphere
    TransformComponent:
      Position: [1.37556696, 2.39745617, 0]
      Rotation: [0, 0, 0]
      Scale: [1, 1, 1]
    MeshComponent:
      AssetID: 10072064586026924578
    RigidBodyComponent:
      BodyType: 1
      Mass: 1
      LinearDrag: 0
      AngularDrag: 0.0500000007
      DisableGravity: false
      IsKinematic: false
      Layer: 0
      Constraints:
        LockPositionX: false
        LockPositionY: false
        LockPositionZ: false
        LockRotationX: false
        LockRotationY: false
        LockRotationZ: false
    SphereColliderComponent:
      Radius: 0.5
      IsTrigger: false
      Material: 0
  - Entity: 14533907289690695312
    Parent: 0
    Children:
      []
    TagComponent:
      Tag: Capsule
    TransformComponent:
      Position: [0, 2.4051888, 0]
      Rotation: [-1.4625982, 0, 0]
      Scale: [1, 1, 1]
    MeshComponent:
      AssetID: 7302828646365096966
    RigidBodyComponent:
      BodyType: 1
      Mass: 1
      LinearDrag: 0
      AngularDrag: 0.0500000007
      DisableGravity: false
      IsKinematic: false
      Layer: 0
      Constraints:
        LockPositionX: false
        LockPositionY: false
        LockPositionZ: false
        LockRotationX: false
        LockRotationY: false
        LockRotationZ: false
    CapsuleColliderComponent:
      Radius: 0.5
      Height: 1
      IsTrigger: false
      Material: 0
  - Entity: 17710473781250652858
    Parent: 0
    Children:
      []
    TagComponent:
      Tag: CubeScene
    TransformComponent:
      Position: [-2.32214236, 2.34247446, 0]
      Rotation: [0, 0, 0]
      Scale: [1.5, 1.5, 1.5]
    MeshComponent:
      AssetID: 16439377475024457093
    RigidBodyComponent:
      BodyType: 1
      Mass: 1
      LinearDrag: 0
      AngularDrag: 0.0500000007
      DisableGravity: false
      IsKinematic: false
      Layer: 0
      Constraints:
        LockPositionX: false
        LockPositionY: false
        LockPositionZ: false
        LockRotationX: false
        LockRotationY: false
        LockRotationZ: false
    MeshColliderComponent:
      IsConvex: true
      IsTrigger: false
      OverrideMesh: false
      Material: 0
  - Entity: 13181667512064341534
    Parent: 0
    Children:
      []
    TagComponent:
      Tag: Camera
    TransformComponent:
      Position: [0, 0.373555422, 3.54624033]
      Rotation: [0, 0, 0]
      Scale: [1, 1, 1]
    CameraComponent:
      Camera:
        ProjectionType: 0
        PerspectiveFOV: 45
        PerspectiveNear: 0.00999999978
        PerspectiveFar: 10000
        OrthographicSize: 10
        OrthographicNear: -1
        OrthographicFar: 1
      Primary: true
PhysicsLayers:
  []