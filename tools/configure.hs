import RecursiveContents (getRecursiveContents)
import System.FilePath
import System.IO
import RecursiveContents (getRecursiveContents)
simpleFind :: (FilePath -> Bool) -> FilePath -> IO [FilePath]
simpleFind p path = do
    names <- getRecursiveContents path
    return (filter p names)

myDrop xs =do
    if null xs
    then do
        outh <- openFile "Makefile" AppendMode 
        hClose outh
    else do 
        outh <- openFile "Makefile" AppendMode     
        hPutStrLn outh ("\t$(OBJDIR)" ++ init (init (drop 1 $ head xs)) ++ ".o \\") 
        hClose outh       
        myDrop (tail xs)
 
myDrop2 xs =do
    if null xs
    then do 
        outh <- openFile "Makefile" AppendMode 
        hClose outh 
    else do 
        outh <- openFile "Makefile" AppendMode     
        hPutStrLn outh ("$(OBJDIR)" ++ init (init (drop 1 $ head xs)) ++ ".o: " ++ (drop 2 $ head xs)) 
        hPutStrLn outh "\t$(CC) -c $< -o $@"
        hClose outh       
        myDrop2 (tail xs)
               

configure :: IO () 
configure = do 
outh <- openFile "Makefile" WriteMode
hPutStrLn outh "CXX=mpiicpx -std=c++11 -O3"
hPutStrLn outh "LIBS=-lgsl -lgslcblas -lmkl_scalapack_lp64 -lmkl_blacs_intelmpi_lp64 -lmkl_intel_lp64 -lmkl_intel_thread -lmkl_core -liomp5"
hPutStrLn outh "OUT = ecode"
hPutStrLn outh "OBJDIR = ./objects"
hPutStrLn outh "LIBOBJS= \\"
hClose outh 
d<-simpleFind (\p -> takeExtension p == ".cpp") "."
myDrop d
outh <- openFile "Makefile" AppendMode
hPutStrLn outh "\n$(OUT): objdir $(LIBOBJS)"
hPutStrLn outh "\t$(CXX) $(LIBOBJS) -o $@ $(LIBS)"
hPutStrLn outh "objdir:"
hPutStrLn outh "\tmkdir -p $(OBJDIR)"
hClose outh 
myDrop2 d
outh <- openFile "Makefile" AppendMode
hPutStrLn outh "clean:"
hPutStrLn outh "\trm -rf $(OBJDIR) $(OUT)"
hClose outh 
