using System;

namespace Hep
{
	public static class Mathf
	{
		public const float Deg2Rad = (float)Math.PI / 180.0F;
		public const float Rad2Deg = 180.0F / (float)Math.PI;

		public static float Clamp(float value, float min, float max)
		{
			if (value < min)
				return min;
			if (value > max)
				return max;
			return value;
		}
	}
}