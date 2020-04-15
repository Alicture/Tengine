/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * License); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * AS IS BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

/*
 * Copyright (c) 2017, Open AI Lab
 * Author: haitao@openailab.com
 */
#include "operator/unsqueeze.hpp"
#include "static_graph.hpp"

namespace TEngine {

bool Unsqueeze::InferShape(const std::vector<TShape>& ishape, std::vector<TShape>& oshape, int layout)
{
    std::vector<int>axises = param_.axises;
   
    const TShape shape = ishape[0];
    std::vector<int> input_dim = shape.GetDim();
    std::vector<int> out_dim = input_dim;
    
    for(unsigned int j =0; j < axises.size();j++)
    {
        int dim_size = (int)out_dim.size();
        int pos = axises[j];
        if(pos < 0)
        {
            pos = pos + dim_size;
        }
        if(pos < 0 || pos > dim_size)
            return false;
        out_dim.insert(out_dim.begin()+pos,1);
    }
    
    oshape[0].SetDim(out_dim);
    oshape[0].SetDataLayout(shape.GetDataLayout());

    return true;
}
void Unsqueeze::SetSchema(void)
{
    Input({"input:float32"})
        .Output({"output:float32"})
        .SetDoc(R"DOC(Unsqueeze Operator)DOC");
}
}    // namespace TEngine
