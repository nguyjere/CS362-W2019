import java.util.Calendar;
import junit.framework.TestCase;
import java.util.Random;

public class UrlValidatorTest extends TestCase {


   public UrlValidatorTest(String testName) {
      super(testName);
   }
	
   public void testManualNull()
   {
	   String fakeNull = null;
	   UrlValidator urlVal = new UrlValidator();
	   assertFalse(urlVal.isValid(fakeNull));
   }
   
   public void testManualPattern()
   {
	   UrlValidator urlVal = new UrlValidator();
	   
	   //nothing close to pattern
	   assertFalse(urlVal.isValid("this is not a URL pattern"));
	   
	   //true pattern
	   assertTrue(urlVal.isValid("http://www.google.com"));
	   assertTrue(urlVal.isValid("https://www.google.com"));
	   assertTrue(urlVal.isValid("ftp://www.google.com"));
	   
	   //missing scheme
	   assertFalse(urlVal.isValid("www.google.com"));
	   
	   //invalid pattern
	   assertFalse(urlVal.isValid("http:/www.google.com"));
	   assertFalse(urlVal.isValid("https://google"));
	   assertFalse(urlVal.isValid("ftp://com"));
	   
   }
   
   public void testManualSchemes()
   {
	   String afterScheme = "://www.example.com";
	   
	   //default schemes
	   UrlValidator urlVal = new UrlValidator();
	   
	   //default schemes should pass, non should fail
	   assertTrue(urlVal.isValid("https" + afterScheme));
	   assertTrue(urlVal.isValid("http" + afterScheme ));
	   assertTrue(urlVal.isValid("ftp" + afterScheme));
	   assertFalse(urlVal.isValid("foo" + afterScheme));
	   assertFalse(urlVal.isValid("bar" + afterScheme));
	   assertFalse(urlVal.isValid("BAZ" + afterScheme));
	   
	   //test with schemes declared
	   String[] schemes = {"foo", "bar", "BAZ"};
	   urlVal = new UrlValidator(schemes);
	   
	   //declared schemes should pass, non decalred should fail
	   assertFalse(urlVal.isValid("https" + afterScheme));
	   assertFalse(urlVal.isValid("http" + afterScheme ));
	   assertFalse(urlVal.isValid("ftp" + afterScheme));
	   assertTrue(urlVal.isValid("foo" + afterScheme));
	   assertTrue(urlVal.isValid("bar" + afterScheme));
	   assertTrue(urlVal.isValid("BAZ" + afterScheme));
	   
   }
   
   public void testManualAuth() {
	   
	   UrlValidator urlVal = new UrlValidator();
	   
	   //valid authority
	   assertTrue(urlVal.isValid("http://www.sample.com"));
	   
	   //missing authority
	   assertFalse(urlVal.isValid("http://"));
	   assertFalse(urlVal.isValid("https://"));
	   assertFalse(urlVal.isValid("ftp://"));
	   
	   //garbage authority
	   assertFalse(urlVal.isValid("http://test"));
	   assertFalse(urlVal.isValid("https://test"));
	   assertFalse(urlVal.isValid("ftp://test"));
   }
 
   
   public void testManualPaths()
   {
	   //all schemes
	   UrlValidator urlVal = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);
	   assertTrue(urlVal.isValid("http://www.google.com/test1"));
	   assertTrue(urlVal.isValid("http://www.google.com/t123"));
	   assertTrue(urlVal.isValid("http://www.google.com/$23"));
	   assertFalse(urlVal.isValid("http://www.google.com/..//file"));
	   assertFalse(urlVal.isValid("http://www.google.com/.."));
	   assertFalse(urlVal.isValid("http://www.google.com/test//file"));
	   assertFalse(urlVal.isValid("https://www.google.com/../"));
	   
   }
   
   public void testManualQueries()
   {
	   UrlValidator urlVal = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);
	   assertTrue(urlVal.isValid("https://www.google.com/?action=view"));
	   assertTrue(urlVal.isValid("https://google.com/?action=edit&mode=up"));
   }
   
   public void testManualFrag()
   {
	   long options = UrlValidator.NO_FRAGMENTS + UrlValidator.ALLOW_ALL_SCHEMES;
	   UrlValidator urlVal = new UrlValidator(options);
	   assertFalse(urlVal.isValid("https://www.google.com/#/hello"));
	   assertTrue(urlVal.isValid("https://www.google.com/hello:"));
	   
   }
	
   public void testSimplePaths()
   {
	   String[] paths = {"index", "index/", "index/etc/", "~index"};
	   UrlValidator urlValidator = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);
	   for (String path : paths) {
		   assertTrue(path, urlValidator.isValid("http://www.example.com/" + path));
	   }
   }
   
   public void testIpAddresses() {
       UrlValidator urlValidator = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);
       for (int i = 0; i < 300; i++)
       {
    	   String url = String.format("https://%d.%d.%d.%d", i, i, i, i);
    	   if (i <= 255 || i == 0)
    	   {
    		   assertTrue(url, urlValidator.isValid(url));
    	   } else {
    		   assertFalse(url, urlValidator.isValid(url));
    	   }
       }
   }

   public void testSchemes()
   {
	   String[] schemes = {"foo", "bar", "BAZ"};
	   UrlValidator urlValidator = new UrlValidator(schemes);
	   for (String scheme : schemes) {
		   assertTrue(scheme, urlValidator.isValid(scheme + "://www.example.com/"));
	   }
   } 
   private static final long TestTimeout = 60 * 500 * 1;
   
   public static String selectMember(Random random, String[] array) {
	      int n = random.nextInt(array.length);
	      return array[n];
	   }
    String[] schemes = {"http://","ftp://","h3t://","://","htp://","","http:/","file://"}; //8
	String[] auths = {"","www.amazon.com","0.0.0.0","amazon.com:80","am.3n","amazon.cc","amazon.com:jhs"}; //7
	String[] paths = {"/file","/file/file2","/..","/#","/file//file3","/etc"}; //6
	String[] queries = {"?action=hide","","?action=hide&mode=up"}; //3
	String[] ports =  {":80", ":65555", ":0", ""};
   public void testSchemerandom()
   {
	
	long startTime = Calendar.getInstance().getTimeInMillis();
	long elapsed = Calendar.getInstance().getTimeInMillis() - startTime;
	System.out.println("Start testing...");
	for (int iteration = 0; elapsed < TestTimeout; iteration++) 
	{
		long randomseed = 10;//System.currentTimeMillis();
		Random random = new Random(randomseed);
		for(int i = 0; i < 500; i++)
		{
			UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
		    String random2 = selectMember(random, schemes);
				String temp = random2 + auths[1];
				urlVal.isValid(temp);	
		}
		elapsed = (Calendar.getInstance().getTimeInMillis() - startTime);
		if ((iteration % 10000) == 0 && iteration != 0)
			System.out.println("elapsed time: " + elapsed + " of " + TestTimeout);
	}
	System.out.println("Done testing...");
   }
   
   public void testauthsrandom()
   {
	
	long startTime = Calendar.getInstance().getTimeInMillis();
	long elapsed = Calendar.getInstance().getTimeInMillis() - startTime;
	System.out.println("Start testing...");
	for (int iteration = 0; elapsed < TestTimeout; iteration++) 
	{
		long randomseed = 10;//System.currentTimeMillis();
		Random random = new Random(randomseed);
		for(int i = 0; i < 500; i++)
		{
			UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
		    String random2 = selectMember(random, auths);
				String temp = schemes[0] + random2;
				urlVal.isValid(temp);	
		}
		elapsed = (Calendar.getInstance().getTimeInMillis() - startTime);
		if ((iteration % 10000) == 0 && iteration != 0)
			System.out.println("elapsed time: " + elapsed + " of " + TestTimeout);
	}
	System.out.println("Done testing...");
   }
   public void testpathsrandom()
   {
	
	long startTime = Calendar.getInstance().getTimeInMillis();
	long elapsed = Calendar.getInstance().getTimeInMillis() - startTime;
	System.out.println("Start testing...");
	for (int iteration = 0; elapsed < TestTimeout; iteration++) 
	{
		long randomseed = 10;//System.currentTimeMillis();
		Random random = new Random(randomseed);
		for(int i = 0; i < 500; i++)
		{
			UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
		    String random2 = selectMember(random, paths);
				String temp = schemes[0] + auths[1]+random2;
				urlVal.isValid(temp);	
		}
		elapsed = (Calendar.getInstance().getTimeInMillis() - startTime);
		if ((iteration % 10000) == 0 && iteration != 0)
			System.out.println("elapsed time: " + elapsed + " of " + TestTimeout);
	}
	System.out.println("Done testing...");
   }
   public void testqueriesrandom()
   {
	
	long startTime = Calendar.getInstance().getTimeInMillis();
	long elapsed = Calendar.getInstance().getTimeInMillis() - startTime;
	System.out.println("Start testing...");
	for (int iteration = 0; elapsed < TestTimeout; iteration++) 
	{
		long randomseed = 10;//System.currentTimeMillis();
		Random random = new Random(randomseed);
		for(int i = 0; i < 500; i++)
		{
			UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
		    String random2 = selectMember(random, queries);
				String temp = schemes[0] +auths[1]+ random2;
				urlVal.isValid(temp);	
		}
		elapsed = (Calendar.getInstance().getTimeInMillis() - startTime);
		if ((iteration % 10000) == 0 && iteration != 0)
			System.out.println("elapsed time: " + elapsed + " of " + TestTimeout);
	}
	System.out.println("Done testing...");
   }
   public void testisvalidrandom()
   {
	
	long startTime = Calendar.getInstance().getTimeInMillis();
	long elapsed = Calendar.getInstance().getTimeInMillis() - startTime;
	System.out.println("Start testing...");
	for (int iteration = 0; elapsed < TestTimeout; iteration++) 
	{
		long randomseed = 10;//System.currentTimeMillis();
		Random random = new Random(randomseed);
		for(int i = 0; i < 500; i++)
		{
			UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
		    String Scheme = selectMember(random, schemes);
		    String Authority = selectMember(random, auths);
		    String Ports = selectMember(random, ports);
		    String Paths = selectMember(random, paths);
		    String Query = selectMember(random, queries);

		    String URL = Scheme + Authority + Ports + Paths + Query;

				urlVal.isValid(URL);	
		}
		elapsed = (Calendar.getInstance().getTimeInMillis() - startTime);
		if ((iteration % 10000) == 0 && iteration != 0)
			System.out.println("elapsed time: " + elapsed + " of " + TestTimeout);
	}
	System.out.println("Done testing...");
   }
}
