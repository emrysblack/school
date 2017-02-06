abstract class Duck
{
   FlyBehavior mFlyBehavior;
   QuackBehavior mQuackBehavior;

   public Duck()
   {
      mFlyBehavior = new FlyWithWings();
      mQuackBehavior = new Quack();
   }

   public abstract void display();

   public void doFly() { mFlyBehavior.fly(); }
   public void doQuack() { mQuackBehavior.quack(); }

   public void swim() { System.out.println("All ducks float, even decoys!"); }

   public void setFlyBehavior(FlyBehavior fb)
   {
      mFlyBehavior = fb;
   }

   public void setQuackBehavior(QuackBehavior qb)
   {
      mQuackBehavior = qb;
   }
}

interface FlyBehavior { public void fly(); }
interface QuackBehavior { public void quack(); }

class MallardDuck extends Duck
{
   public void display()
   { // looks like a mallard
   }
}

class RedheadDuck extends Duck
{
   public void display()
   { // looks like a redhead
   }
}

class FlyWithWings implements FlyBehavior
{
   public void fly()
   {
      System.out.println("I'm flying!!");
   }
}

class FlyNoWay implements FlyBehavior
{
   public void fly()
   {
      System.out.println("I can't fly.");
   }
}

class Quack implements QuackBehavior
{
   public void quack()
   {
      System.out.println("Quack");
   }
}

class MuteQuack implements QuackBehavior
{
   public void quack()
   {
      System.out.println("<< Silence >>");
   }
}

class Squeak implements QuackBehavior
{
   public void quack()
   {
      System.out.println("Squeak");
   }
}

class ModelDuck extends Duck
{
   ModelDuck()
   {
      mFlyBehavior = new FlyNoWay(); // grounded!
      mQuackBehavior = new Quack();
   }

   public void display()
   {
      System.out.println("I'm a model duck.");
   }
}

class FlyRocketPowered implements FlyBehavior
{
   public void fly() { System.out.println("I'm flying with a rocket!"); }
}

public class MiniDuckSimulator
{
   public static void main(String[] args)
   {
      Duck mallard = new MallardDuck();
      mallard.doQuack();
      mallard.doFly();

      Duck model = new ModelDuck();
      model.doFly();
      model.setFlyBehavior(new FlyRocketPowered());
      model.doFly();
   }
}

