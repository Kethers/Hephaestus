using System;
using Hep;

namespace ExampleApp
{
	public class DirectionVectorsTest : Entity
	{
		private TagComponent m_Tag;
		private TransformComponent m_Transform;

		void OnCreate()
		{
			m_Tag = GetComponent<TagComponent>();
			m_Transform = GetComponent<TransformComponent>();
		}

		void OnUpdate(float ts)
		{
			Transform worldSpaceTransform = m_Transform.GetWorldSpaceTransform();

			Console.WriteLine($"{m_Tag.Tag} Translation: {worldSpaceTransform.Position}");
			Console.WriteLine($"{m_Tag.Tag} Rotation: {worldSpaceTransform.Rotation}");
			Console.WriteLine($"{m_Tag.Tag} Scale: {worldSpaceTransform.Scale}");

			Console.WriteLine($"{m_Tag.Tag} Up: {worldSpaceTransform.Up}");
			Console.WriteLine($"{m_Tag.Tag} Forward: {worldSpaceTransform.Forward}");
			Console.WriteLine($"{m_Tag.Tag} Right: {worldSpaceTransform.Right}");
		}
	}
}