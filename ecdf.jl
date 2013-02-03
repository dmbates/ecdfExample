using DataFrames

dat = read_rda("/home/bates/Rproj/ecdfExample/data.rda");
sref = dat["ref"].data;
@elapsed sref = sort!(sref)  # an in-place sort as ref is no longer needed
samp = dat["samp"].data;
numlt2 = dat["numlt2"].data;
dump(sref)
dump(samp)
dump(numlt2)
numlt4 = [searchsortedlast(sref, s) for s in samp];
@elapsed [searchsortedlast(sref, s) for s in samp]
@assert (all(numlt4 .== numlt2))

ord = sortperm(samp);
@elapsed sortperm(samp)
dump(ord)

function julcp(samp::Vector{Float64}, sref::Vector{Float64}, ord::Vector{Int})
    j = 1
    ans = similar(ord)
    for i in 1:length(samp)
        while (sref[j] < samp[ord[i]] && j <= length(sref)) j += 1 end
        ans[ord[i]] = j - 1
    end
    ans
end

numlt5 = julcp(samp, sref, ord);
@elapsed julcp(samp, sref, ord)
@assert all(numlt5 .== numlt2)

