Scene: Scene Name
Environment:
  AssetPath: assets\env\birchwood_4k.hdr
  Light:
    Direction: [0, 0, 0]
    Radiance: [0, 0, 0]
    Multiplier: 1
Entities:
  - Entity: 10790878375657664772
    Parent: 18033725156078219843
    Children:
      []
    TagComponent:
      Tag: Sphere
    TransformComponent:
      Position: [-1.24961185, 4.25943899, 3.38380265]
      Rotation: [0, 0, 0]
      Scale: [1, 1, 1]
    MeshComponent:
      AssetID: 14983128427839407070
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
  - Entity: 18033725156078219843
    Parent: 0
    Children:
      - Handle: 10790878375657664772
    TagComponent:
      Tag: Sphere
    TransformComponent:
      Position: [-2.73042727, 3.68213511, 3.38380265]
      Rotation: [0, 0, 0]
      Scale: [1, 1, 1]
    MeshComponent:
      AssetID: 14983128427839407070
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
  - Entity: 16634993330455190223
    Parent: 0
    Children:
      []
    TagComponent:
      Tag: Sphere
    TransformComponent:
      Position: [-2.78621578, 5.48215866, -1.33405685]
      Rotation: [0, 0, 0]
      Scale: [1, 1, 1]
    MeshComponent:
      AssetID: 14983128427839407070
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
  - Entity: 12975938672247153436
    Parent: 0
    Children:
      []
    TagComponent:
      Tag: Cube
    TransformComponent:
      Position: [-2.01373863, 4.03783751, 2.91641903]
      Rotation: [9.9061559e-08, 0.719529092, -0.70863378]
      Scale: [0.389999807, 0.389999926, 0.389999837]
    MeshComponent:
      AssetID: 8065591610254392454
    RigidBodyComponent:
      BodyType: 1
      Mass: 0.200000003
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
  - Entity: 13882838760121718506
    Parent: 0
    Children:
      []
    TagComponent:
      Tag: Directional Light
    TransformComponent:
      Position: [0, 0, 0]
      Rotation: [2.50669408, 0.501803458, 0.136891216]
      Scale: [1, 0.999998569, 0.999998987]
    DirectionalLightComponent:
      Radiance: [1, 1, 1]
      CastShadows: true
      SoftShadows: true
      LightSize: 0.5
  - Entity: 2143608321399101581
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
      EnvironmentAssetPath: assets\env\birchwood_4k.hdr
      Intensity: 0.75
      Angle: 0
  - Entity: 17035936673948473165
    Parent: 0
    Children:
      []
    TagComponent:
      Tag: Mesh
    TransformComponent:
      Position: [0, 0, 0]
      Rotation: [0, 0, 0]
      Scale: [1, 1, 1]
    MeshComponent:
      AssetID: 11407590181439473350
    RigidBodyComponent:
      BodyType: 0
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
      IsConvex: false
      IsTrigger: false
      OverrideMesh: false
      Material: 14036329762669544384
  - Entity: 5561134054991576534
    Parent: 0
    Children:
      - Handle: 12392346523579991874
    TagComponent:
      Tag: Player
    TransformComponent:
      Position: [2.71265602, 1.24520636, 4.11461163]
      Rotation: [0, 0, 0]
      Scale: [1, 1, 1]
    ScriptComponent:
      ModuleName: FPSExample.FPSPlayer
      StoredFields:
        - Name: WalkingSpeed
          Type: 1
          Data: 3
        - Name: RunSpeed
          Type: 1
          Data: 5
        - Name: JumpForce
          Type: 1
          Data: 1
        - Name: MouseSensitivity
          Type: 1
          Data: 4
    MeshComponent:
      AssetID: 17523092873766587173
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
        LockRotationX: true
        LockRotationY: true
        LockRotationZ: true
    MeshColliderComponent:
      IsConvex: true
      IsTrigger: false
      OverrideMesh: false
      Material: 0
  - Entity: 12392346523579991874
    Parent: 5561134054991576534
    Children:
      []
    TagComponent:
      Tag: Camera
    TransformComponent:
      Position: [0, 1, 0]
      Rotation: [0, 0.785398185, 0]
      Scale: [1, 1, 1]
    CameraComponent:
      Camera:
        ProjectionType: 0
        PerspectiveFOV: 65
        PerspectiveNear: 0.100000001
        PerspectiveFar: 1000
        OrthographicSize: 10
        OrthographicNear: -1
        OrthographicFar: 1
      Primary: true
PhysicsLayers:
  []